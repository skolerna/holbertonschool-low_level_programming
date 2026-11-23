# Memory Maps — Analyse de la mémoire en C

## 1. Stack Example (`stack_example.c`)

### Fonctionnement

Ce programme illustre la récursivité et la durée de vie des variables locales.

Chaque appel de `walk_stack()` possède son propre `stack frame`, contenant ses paramètres et sa variable `marker`.

### Memory maps

**Étape 1 — Récursivité (`depth = 3`)**

État après le retour de `dump_frame("enter", 3)` :

```text
STACK
├── walk_stack(3) : marker = 30
├── walk_stack(2) : marker = 20
├── walk_stack(1) : marker = 10
├── walk_stack(0) : marker = 0
└── main()

HEAP : aucune allocation dynamique
```

Les quatre `marker` existent simultanément, dans des `stack frames` distincts.

| depth | marker | Adresse observée |
|---|---|---|
| 0 | 0 | `0x7fffc4bb6e54` |
| 1 | 10 | `0x7fffc4bb6e24` |
| 2 | 20 | `0x7fffc4bb6df4` |
| 3 | 30 | `0x7fffc4bb6dc4` |

**Étape 2 — Pendant `dump_frame("enter", 2)`**

```text
STACK
├── dump_frame(2)
│   ├── local_int = 102
│   │   &local_int = 0x7fffc4bb6da4
│   │          ▲
│   ├── p_local ─┘
│   │   valeur = 0x7fffc4bb6da4
│   ├── local_buf[16]
│   │   [0] = 'C', [1] = '\0'
│   ├── depth = 2
│   └── label ──> "enter"
├── walk_stack(2) : marker = 20
├── walk_stack(1) : marker = 10
├── walk_stack(0) : marker = 0
└── main()
```

`p_local` contient l'adresse de `local_int`, donc `*p_local = 102`. Les autres éléments de `local_buf` ne sont pas initialisés. La chaîne littérale `"enter"` possède une durée de vie statique.

**Étape 3 — Retour des fonctions**

Lorsque `walk_stack(3)` retourne :

```text
STACK
├── walk_stack(2) : marker = 20
├── walk_stack(1) : marker = 10
├── walk_stack(0) : marker = 0
└── main()

marker = 30 : durée de vie terminée
```

Les variables locales cessent d'être valides au retour de leur fonction.

Les appels `dump_frame("enter", 2)` et `dump_frame("exit", 2)` ont affiché la même adresse pour `local_int` (`0x7fffc4bb6da4`).

Cela ne signifie pas que l'ancienne variable est encore valide : une nouvelle variable a réutilisé le même emplacement mémoire.

---

## 2. Heap Example (`heap_example.c`)

### Fonctionnement

`person_new()` effectue deux allocations avec `malloc()` pour chaque personne : une structure `Person` et un tableau de caractères pour son nom.

### Memory maps

**Étape 1 — Après les allocations**

```text
STACK                     HEAP

alice ──────────────────> Person A (age = 30)
                           └── name ──> "Alice\0" (6 bytes)

bob ────────────────────> Person B (age = 41)
                           └── name ──> "Bob\0" (4 bytes)
```

Les pointeurs `alice` et `bob` sont locaux à `main()`. Les allocations restent valides après le retour de `person_new()`.

**Étape 2 — Libérations**

| Instruction | Résultat |
|---|---|
| `free(bob->name)` | Nom de Bob libéré |
| `free(bob)` | Structure de Bob libérée |
| `person_free_partial(alice)` | Structure d'Alice libérée, mais pas son nom |

**Memory map après les libérations :**

```text
HEAP
├── Person A : libérée
├── "Alice\0" : toujours alloué
│                MEMORY LEAK : 6 bytes
├── Person B : libérée
└── "Bob\0" : libéré
```

L'allocation contenant `"Alice"` est devenue inaccessible, car le pointeur permettant de la retrouver était stocké dans la structure libérée.

### Memory ownership et object lifetimes

Après le retour de `person_new()`, `main()` est responsable de la libération des deux allocations de chaque personne.

`free(p)` libère seulement l'allocation pointée par `p`, pas les allocations référencées par ses membres.

Bob est correctement libéré. Pour Alice, l'absence de `free(alice->name)` avant la libération de sa structure provoque une `memory leak`.

---

## 3. Aliasing Example (`aliasing_example.c`)

### Fonctionnement

`make_numbers(5)` alloue un tableau d'entiers sur le `heap`.

L'instruction `b = a` crée un `pointer aliasing` : `a` et `b` contiennent la même adresse.

### Memory maps

**Étape 1 — Avant `free(a)`**

```text
STACK                    HEAP

a ──────┐
        ├───────────────> int[5]
b ──────┘                  [0, 11, 22, 33, 44]
                           0x5bf36038a420
```

Les deux pointeurs référencent la même allocation. `b = a` ne crée aucune copie du tableau.

**Étape 2 — Après `free(a)`**

```text
STACK                    HEAP

a ─ ─ ─┐
       ├ ─ ─ ─ ─ ─ ─ ─ > [int[5] libéré]
b ─ ─ ─┘

a et b : dangling pointers
```

`free(a)` termine la durée de vie de l'unique allocation. `b` n'est pas automatiquement mis à `NULL`.

**Étape 3 — Use-after-free**

Le programme lit `b[2]`, écrit dans `b[3]`, puis relit `b[3]` après la libération.

Résultat observé sans Valgrind :

```text
a=0x5bf36038a420 b=0x5bf36038a420 a[2]=22 b[2]=22
after free(a): b=0x5bf36038a420 (dangling)
reading b[2]=-522502888
wrote b[3]=1234
```

Les valeurs affichées après `free(a)` ne sont pas fiables : les accès provoquent un `undefined behavior`, même si le programme continue de fonctionner.

GCC a détecté le `use-after-free`. La compilation avec `make` a nécessité `-Wno-error=use-after-free` pour conserver les warnings sans bloquer la compilation.

### Memory ownership

L'allocation retournée par `make_numbers()` devient la responsabilité de `main()`.

Même si deux pointeurs la référencent, il n'existe qu'un seul tableau à libérer.

---

## 4. Crash Example (`crash_example.c`)

### Fonctionnement

`main()` initialise `n = 0` et `nums = NULL`.

La fonction `allocate_numbers(0)` retourne `NULL` avant l'allocation, car `n <= 0`.

### Memory maps

**Étape 1 — Pendant `allocate_numbers(0)`**

```text
STACK
├── allocate_numbers(0)
│   ├── n = 0
│   └── arr = NULL
└── main()
    ├── n = 0
    └── nums = NULL

HEAP : aucune allocation
```

**Étape 2 — Après le retour**

```text
STACK
└── main()
    ├── n = 0
    └── nums = NULL ──> aucun objet valide

HEAP : aucune allocation
```

Le `stack frame` de `allocate_numbers()` n'est plus actif.

**Étape 3 — NULL pointer dereference**

```c
nums[0] = 42;
```

Cette instruction tente d'écrire à travers `NULL`, qui ne référence aucun objet valide.

Résultat observé sans Valgrind :

```text
requesting n=0
Segmentation fault
```

Il s'agit d'un `undefined behavior`. Le `Segmentation fault` a été observé sous Ubuntu, mais n'est pas garanti par le langage C.

Aucune allocation n'a été créée sur le `heap`. L'instruction `free(nums)` n'a pas été atteinte.

---

## 5. Vérification critique et correction de l'IA

J'ai utilisé l'IA pour générer des `memory maps` des quatre programmes, puis j'ai comparé ses explications au code source et aux résultats d'exécution afin de vérifier leur exactitude.

### Explication initiale incomplète

La première `memory map` générée par l'IA pour `stack_example.c` montrait uniquement les appels de `walk_stack()` et les variables `marker`.

Elle ne représentait pas le `stack frame` temporaire de `dump_frame()`.

### Pourquoi cette explication était incomplète

Pendant `dump_frame()`, les variables `local_int`, `local_buf` et `p_local` existent également.

Sans ces variables, la `memory map` ne permettait pas d'identifier correctement la relation entre `p_local` et `local_int`, ni leur durée de vie.

### Correction apportée

J'ai ajouté une deuxième `memory map` représentant `dump_frame("enter", 2)`.

Elle montre que `p_local` contient l'adresse de `local_int` et que leurs durées de vie se terminent au retour de la fonction.

La correction permet aussi de distinguer les `stack frames` actifs des appels déjà terminés.

### Autres vérifications

- **Stack :** une adresse réutilisée ne signifie pas que l'ancienne variable est toujours valide.
- **Heap :** `free(p)` ne libère pas automatiquement les allocations référencées par `p->name`.
- **Aliasing :** les accès via `b` après `free(a)` sont invalides, même si le programme affiche des valeurs.
- **Crash :** le `Segmentation fault` est un résultat observé, pas un comportement garanti.

Ces vérifications permettent de distinguer les observations réelles des règles de validité mémoire en C.

---

## Conclusion

Les quatre programmes illustrent les différences entre `stack` et `heap`, les durées de vie des variables, le `memory ownership` et les risques liés aux pointeurs.

Les `memory maps` permettent de suivre les allocations, les `pointer aliases` et les moments où les objets deviennent invalides.

L'analyse critique de l'IA a permis d'identifier une représentation incomplète, de la corriger et de justifier les modifications à partir du code source et des résultats d'exécution.
