#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef __SORT_H_
#define __SORT_H_

enum order_types
{
    ASCENDING,
    INCREASING
};

int *create_random_array(int array_size);
int *create_sorted_array(int array_size, int order_type);
void swap(int *x, int *y);
int pop(int **ar, int size, int index);
int counter(int *array, int size, int search);

double test_algo(char *func_name, void (*sort)(int **, int));

void bubble_sort(int **array, int size);
void selection_sort(int **array, int size);
void insertion_sort(int **array, int size);

int partition(int **array, int low, int high);
void quick_sort(int **array, int low, int high);
void quick_sort_for_test(int **array, int size);

void merge(int *arr, int l, int m, int r);
void merge_sort(int arr[], int l, int r);
void merge_sort_for_test(int **array, int size);

int get_max(int *array, int size);
void bucket_sort(int **array, int size);

void shell_sort(int **array, int n);

void swap_double(double *x, double *y);
void bubble_sort_double(double **array, int size);
double find_largest_n(double *ar, int size, int n);

#endif