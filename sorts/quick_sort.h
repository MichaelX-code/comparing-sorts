#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "common.h"

void
quick_sort_internal(int * arr, int l, int r)
{
    int i = l, j = r;
    int pivot = arr[r];
    while (i <= j) {
        while (arr[i] < pivot)
            ++i;
        while (arr[j] > pivot)
            --j;
        if (i <= j) {
            swap(&arr[i], &arr[j]);
            --j;
            ++i;
        }
    }

    if (l < j)
        quick_sort_internal(arr, l, j);
    if (i < r)
        quick_sort_internal(arr, i, r);
}

void
quick_sort(int * arr, int size)
{
    quick_sort_internal(arr, 0, size - 1);
}

#endif // QUICK_SORT_H