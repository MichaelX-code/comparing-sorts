#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#include "sorts/quick_sort.h"
#include "sorts/merge_sort.h"
#include "sorts/heap_sort.h"

#define ARR_SIZE 1000000
#define N_SIZES 4
int arr_sizes[] = { 50000, 100000, 500000, 1000000 };
int arr[ARR_SIZE];
double results[N_SIZES];

void generate_arr();
void print_arr();
void benchmark_sort();
bool is_sorted();

int
main(void)
{
    // Write header into csv
    FILE * out_file = fopen("results.csv", "w");

    fprintf(out_file, "Sort Name");
    for (int i = 0; i < N_SIZES; ++i)
        fprintf(out_file, ",%d", arr_sizes[i]);
    fprintf(out_file, "\n");

    fclose(out_file);

    // Benchmark all sorts
    benchmark_sort("Quick Sort", quick_sort);
    benchmark_sort("Merge Sort", merge_sort);
    benchmark_sort("Heap Sort", heap_sort);

    return 0;
}

void
generate_arr(int size)
{
    for (int i = 0; i < size; ++i)
        arr[i] = rand();
}

void
print_arr(int size)
{
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

void
save_results(char * sort_name)
{
    FILE * out_file = fopen("results.csv", "a");

    fprintf(out_file, "%s", sort_name);
    for (int i = 0; i < N_SIZES; ++i)
        fprintf(out_file, ",%f", results[i]);
    fprintf(out_file, "\n");

    fclose(out_file);
}

void
benchmark_sort(char * sort_name, void sort())
{
    for (int experiment = 0; experiment < N_SIZES; ++experiment) {
        int size = arr_sizes[experiment];
        generate_arr(size);

        clock_t begin = clock();
        sort(arr, size);
        clock_t end = clock();

        double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
        results[experiment] = time_spent;

        assert(is_sorted(arr_sizes[experiment]) && "🚫 Array was not sorted");
    }

    save_results(sort_name);
}

bool
is_sorted(int size)
{
    for (int i = 0; i < size - 1; ++i)
        if (arr[i] > arr[i + 1])
            return (false);
    return (true);
}
