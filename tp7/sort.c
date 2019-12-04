#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "sort.h"
#define BUCKET_SIZE 1

void is_sorted(int *array, int size)
{
    for (int i = 1; i < size; i++)
        if (array[i] > array[i - 1])
        {
            printf("NOT SORTED MAN\n");
            return;
        }
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int pop(int **ar, int size, int index)
{
    int *cursor = *ar;
    int ret_val = cursor[index];

    for (int i = index + 1; i < size; ++i)
    {
        swap(&cursor[i - 1], &cursor[i]);
    }
    cursor[size - 1] = -1;
    return ret_val;
}

int get_max(int *array, int size)
{
    int max = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

int get_min(int *array, int size)
{
    int min = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] < min)
            min = array[i];
    return min;
}

int *create_random_array(int array_size)
{
    int *sorted_ar = malloc(array_size * sizeof(int));
    int *ar = malloc(array_size * sizeof(int));

    for (int i = 0; i < array_size; ++i)
        sorted_ar[i] = i;

    int sorted_ar_size = array_size;
    for (int i = 0; i < array_size; i++)
    {
        int rand_index = rand() % sorted_ar_size;
        ar[i] = pop(&sorted_ar, sorted_ar_size, rand_index);
        sorted_ar_size--;
    }
    free(sorted_ar);
    return ar;
}

int *create_sorted_array(int array_size, int order_type)
{
    int *ar = malloc(array_size * sizeof(int));
    if (order_type == ASCENDING)
    {
        for (int i = 0; i < array_size; i++)
            ar[i] = array_size - i;
    }
    else
    {
        for (int i = 0; i < array_size; i++)
            ar[i] = i;
    }
    return ar;
}

int counter(int *array, int size, int search)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (array[i] == search)
            count++;
    }
    return count;
}

void bubble_sort(int **array, int size)
{
    int *cur = *array;
    for (int i = 0; i < size; i++)
        for (int j = i; j < size; j++)
            if (cur[i] < cur[j])
                swap(&cur[i], &cur[j]);
}

void selection_sort(int **array, int size)
{
    int *arr = *array;
    int min_idx = 0;
    for (int i = 0; i < size - 1; i++)
    {
        min_idx = i;
        for (int j = i + 1; j < size; j++)
            if (arr[j] > arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

void insertion_sort(int **array, int size)
{
    int *arr = *array;
    int key = 0;
    int j = 0;
    for (int i = 1; i < size; i++)
        for (int j = i - 1; j >= 0; j--)
            if (arr[j] < arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

double test_algo(char *func_name, void (*sort)(int **, int))
{
    int *randoms[3], *ascendings[3], *increasings[3];
    int **all_array[] = {randoms, ascendings, increasings};
    double res = 0.0;
    for (int i = 0; i < 3; i++)
    {
        randoms[i] = create_random_array((int)pow(10, i + 2));
        ascendings[i] = create_sorted_array((int)pow(10, i + 2), ASCENDING);
        increasings[i] = create_sorted_array((int)pow(10, i + 2), INCREASING);
    }
    char *types[] = {"sorted", "reversed", "random"};
    for (int i = 0; i < 3; i++)
    {
            for (int j = 0; j < 3; ++j)
        {
            clock_t start = clock();
            sort(&all_array[i][j], (int)pow(10, j + 2));
            is_sorted(all_array[i][j], (int)pow(10, j + 2));
            free(all_array[i][j]);
            clock_t stop = clock();
            double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
            printf("Time elapsed for %s\t in %s\t size %i\t ms: %.5f\n", func_name,types[i], (int)pow(10, i + 2), elapsed);
            res += elapsed;
        }
    }
    return res;
}

void quick_sort(int *ar, int size)
{
    if (size <= 1)
        return;
    int piv_pos = 1;
    swap(&ar[0], &ar[size / 2]);
    for (int i = 0; i < size; i++)
    {
        if (ar[0] < ar[i])
            swap(&ar[i], &ar[piv_pos++]);
    }
    swap(&ar[0], &ar[piv_pos - 1]);

    quick_sort(ar, piv_pos - 1);
    quick_sort(ar + piv_pos, size - piv_pos);
}

void quick_sort_for_test(int **array, int size)
{
    quick_sort(*array, size);
}

void merge(int *arr, int l, int m, int r)
{
    int j, k;
    int left_size = m - l + 1;
    int right_size = r - m;

    int left_ar[left_size], right_ar[right_size];

    for (int i = 0; i < left_size; i++)
        left_ar[i] = arr[l + i];
    for (j = 0; j < right_size; j++)
        right_ar[j] = arr[m + 1 + j];

    int l_ind = 0;
    int r_ind = 0;
    int ar_ind = l;
    while (l_ind < left_size && r_ind < right_size)
    {
        if (left_ar[l_ind] > right_ar[r_ind])
            arr[ar_ind++] = left_ar[l_ind++];
        else
            arr[ar_ind++] = right_ar[r_ind++];
    }

    while (l_ind < left_size)
        arr[ar_ind++] = left_ar[l_ind++];

    while (r_ind < right_size)
        arr[ar_ind++] = right_ar[r_ind++];
}

void merge_sort(int *arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge_sort_for_test(int **array, int size)
{
    merge_sort(*array, 0, size);
}

void append(int *array, int size, int value)
{
    for (int i = 0; i < size; i++)
        if (array[i] == 0)
        {
            array[i] = value;
            return;
        }
}

void bucket_sort(int **array, int size)
{
    int *cur = *array;
    int min = get_min(cur, size);
    int max = get_max(cur, size);

    int bucket_count = (int)((max - min) / BUCKET_SIZE) + 1;
    int *buckets[bucket_count];

    for (int i = 0; i < bucket_count; i++)
    {
        buckets[i] = malloc(BUCKET_SIZE * sizeof(int));
        for (int j = 0; j < BUCKET_SIZE; j++)
            buckets[i][j] = 0;
    }

    for (int i = 0; i < bucket_count; i++)
    {
        int ind = (cur[i] - min) / BUCKET_SIZE;
        append(buckets[ind], BUCKET_SIZE, cur[i]);
    }
    int ar_ind = 0;
    for (int i = bucket_count - 1; i >= 0; i--)
    {
        quick_sort_for_test(&(buckets[i]), BUCKET_SIZE);
        for (int j = BUCKET_SIZE - 1; j >= 0; j--)
        {
            cur[ar_ind++] = buckets[i][j];
        }
    }
}

void shell_sort(int **array, int size)
{
    int* cur = *array;
    int inc = size/2;
    while (inc != 0)
    {
        for (int i = inc; i < size; i++)
        {
            int el = cur[i];
            while (i >= inc && cur[i - inc] < el)
            {
                cur[i] = cur[i - inc];
                i-=inc;
            }
            cur[i] = el;
        }
        if (inc == 2)
            inc = 1;
        else{
            inc = (int)(inc*5/11);
        }
    }
    
}