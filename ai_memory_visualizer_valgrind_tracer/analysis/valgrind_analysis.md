# Valgrind Analysis — Analyse des erreurs mémoire

## Méthode

Les quatre programmes ont été analysés avec Valgrind Memcheck :

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./nom_du_programme
```

J'ai utilisé l'IA pour interpréter les rapports, puis vérifié ses explications à partir du code source, des résultats Valgrind et des `memory maps` de la tâche 0.

## 1. Résumé des résultats

| Programme | Résultat Valgrind | Cause |
|---|---|---|
| `stack_example` | 0 erreur | Aucun accès mémoire invalide détecté |
| `heap_example` | 6 bytes `definitely lost` | Nom d'Alice non libéré |
| `aliasing_example` | 2 `Invalid reads`, 1 `Invalid write` | `use-after-free` |
| `crash_example` | 1 `Invalid write`, `SIGSEGV` | `NULL pointer dereference` |

Aucune utilisation de valeurs non initialisées n'a été signalée lors des quatre exécutions.

---

## 2. Stack Example — Aucune erreur

```text
in use at exit: 0 bytes in 0 blocks
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts
```

Les variables locales sont utilisées pendant leur durée de vie et les pointeurs n'accèdent pas à des objets invalides.

Valgrind comptabilise une allocation de 1 024 bytes, correctement libérée, vraisemblablement liée au buffering de la bibliothèque C.

Ce résultat est cohérent avec les `stack frames` étudiés dans la tâche 0.

## 3. Heap Example — Memory leak

```text
6 bytes in 1 blocks are definitely lost
    by person_new (heap_example.c:21)
    by main (heap_example.c:51)

ERROR SUMMARY: 1 errors from 1 contexts
```

La ligne 21 alloue 6 bytes pour `"Alice\0"`.

`person_free_partial(alice)` libère uniquement la structure `Person`, sans libérer `alice->name`.

L'adresse du nom était conservée dans la structure libérée : les 6 bytes restent alloués mais deviennent inaccessibles.

C'est une `memory leak` classée `definitely lost`, causée par une perte d'accès à l'allocation.

**Ownership :** `main()` doit libérer séparément la structure et son nom. Les deux allocations de Bob sont correctement libérées.

## 4. Aliasing Example — Use-after-free

| Ligne | Diagnostic | Cause |
|---|---|---|
| 42 | `Invalid read of size 4` | Lecture de `b[2]` |
| 44 | `Invalid write of size 4` | Écriture dans `b[3]` |
| 45 | `Invalid read of size 4` | Nouvelle lecture de `b[3]` |

```text
Block was alloc'd by make_numbers (aliasing_example.c:12)
Block was free'd by main (aliasing_example.c:38)
ERROR SUMMARY: 3 errors from 3 contexts
```

`b = a` crée deux `pointer aliases` vers un seul tableau de 20 bytes.

Après `free(a)`, cette allocation n'est plus valide. Les accès via `b` sont donc des `use-after-free`.

Valgrind localise les accès à 8 et 12 bytes du début de l'ancien bloc : ils étaient dans les limites du tableau, mais sa durée de vie est terminée.

La lecture de `b[2]` a affiché `22` sous Valgrind, contre `-522502888` normalement. Ces valeurs ne sont pas garanties (`undefined behavior`).

Aucune `memory leak` n'est détectée, car le tableau a bien été libéré.

La compilation avec `make` a nécessité `-Wno-error=use-after-free` pour conserver les warnings sans les rendre bloquants.

## 5. Crash Example — NULL pointer dereference

```text
Invalid write of size 4
    at main (crash_example.c:32)

Address 0x0 is not stack'd, malloc'd or (recently) free'd
Process terminating with signal 11 (SIGSEGV)

still reachable: 1,024 bytes
ERROR SUMMARY: 1 errors from 1 contexts
```

`allocate_numbers(0)` retourne `NULL` sans appeler `malloc()`.

À la ligne 32, `nums[0] = 42` tente d'écrire 4 bytes à l'adresse `0x0`, ce qui provoque un `Invalid write`.

Cet accès entraîne un `SIGSEGV` sur Ubuntu. Il s'agit d'un `undefined behavior`, et non d'un crash garanti par le langage C.

Les 1 024 bytes `still reachable` correspondent au buffer de sortie de la bibliothèque C (`_IO_file_doallocate`), encore alloué lors de l'arrêt brutal.

Ils ne représentent pas une `memory leak` du tableau `nums`, qui n'a jamais été alloué.

---

## 6. Vérification critique de l'IA

### Explication initiale incomplète

Pour `crash_example.c`, l'IA indiquait qu'aucune allocation n'était effectuée sur le `heap`.

### Pourquoi c'était incomplet

`allocate_numbers(0)` n'appelle effectivement pas `malloc()`, mais Valgrind indique 1 024 bytes `still reachable`.

La stack trace identifie une allocation de `_IO_file_doallocate`, liée au buffer de sortie de la bibliothèque C.

### Correction

Aucun tableau dynamique n'est alloué par le programme, mais la bibliothèque C effectue une allocation interne.

Cette allocation n'est pas responsable du crash. **La cause directe est l'écriture à travers `nums == NULL`.**

Cette distinction a été vérifiée à partir du code, du rapport Valgrind et de la `memory map` de la tâche 0.

---

## Conclusion

Valgrind a permis d'identifier une `memory leak`, trois accès `use-after-free` et un `NULL pointer dereference`.

Chaque diagnostic a été relié à une instruction précise et à la durée de vie de l'objet concerné.

La vérification critique de l'IA a permis de corriger une explication incomplète et de distinguer les allocations du programme de celles de la bibliothèque C.