
#include <stdio.h>
#include <time.h>

#define DATASET_SIZE 50000
#define SEED_VALUE 42u

static int dataset[DATASET_SIZE];

static unsigned int next_value(unsigned int *state)
{
	unsigned int value;

	*state = (*state * 1103515245u) + 12345u;
	value = *state;
	return (value);
}

static void build_dataset(void)
{
	unsigned int state;
	int i;

	state = SEED_VALUE;

	for (i = 0; i < DATASET_SIZE; i++)
		dataset[i] = (int)(next_value(&state) % 100000);
}

static void process_dataset(void)
{
	int i;
	int v;

	for (i = 0; i < DATASET_SIZE; i++)
	{
		v = dataset[i];
		v = (v * 3) + (v / 7) - (v % 11);
		if (v < 0)
			v = -v;
		dataset[i] = v;
	}
}

static unsigned long reduce_checksum(void)
{
	unsigned long sum;
	int i;

	sum = 0;
	for (i = 0; i < DATASET_SIZE; i++)
		sum = (sum * 131ul) + (unsigned long)dataset[i];

	return (sum);
}

/**
 * main - Measures CPU time for dataset operations
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	unsigned long checksum;
	clock_t start;
	clock_t end;
	clock_t total_start;
	clock_t total_end;
	float elapsed_build;
	float elapsed_process;
	float elapsed_reduce;
	float elapsed_total;

	total_start = clock();

	start = clock();
	build_dataset();
	end = clock();
	elapsed_build = (float)(end - start) / CLOCKS_PER_SEC;

	start = clock();
	process_dataset();
	end = clock();
	elapsed_process = (float)(end - start) / CLOCKS_PER_SEC;

	start = clock();
	checksum = reduce_checksum();
	end = clock();
	elapsed_reduce = (float)(end - start) / CLOCKS_PER_SEC;

	total_end = clock();
	elapsed_total = (float)(total_end - total_start) / CLOCKS_PER_SEC;

	if (checksum == 0ul)
		printf("impossible\n");

	printf("TOTAL seconds: %.6f\n", elapsed_total);
	printf("BUILD_DATA seconds: %.6f\n", elapsed_build);
	printf("PROCESS seconds: %.6f\n", elapsed_process);
	printf("REDUCE seconds: %.6f\n", elapsed_reduce);

	return (0);
}
