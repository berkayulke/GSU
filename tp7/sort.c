#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "sort.h"

void swap(int* x,int*y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int pop(int** ar,int size,int index){
    int* cursor = *ar;
    int ret_val = cursor[index];
    
    for (int i = index+1; i < size; ++i)
    {
        swap(&cursor[i-1],&cursor[i]);
    }
    cursor[size-1] = -1;
    return ret_val;
}

int* create_random_array(int array_size){
    int* sorted_ar = malloc(array_size*sizeof(int)); 
    int* ar = malloc(array_size*sizeof(int));
    
    for (int i = 0; i < array_size; ++i)
        sorted_ar[i] = i;
    
    int sorted_ar_size = array_size;
    for (int i = 0; i < array_size; i++)
    {
        int rand_index = rand()%sorted_ar_size;
        ar[i] = pop(&sorted_ar,sorted_ar_size,rand_index);
        sorted_ar_size--;
    }
    free(sorted_ar);
    return ar;
}

int* create_sorted_array(int array_size,int order_type){
    int* ar = malloc(array_size*sizeof(int));
    if (order_type == ASCENDING)
    {
        for(int i = 0; i < array_size; i++)
            ar[i] = array_size-i;
    }
    else{
        for (int i = 0; i < array_size; i++)
            ar[i] = i;
    }
    return ar;
}

int counter(int* array,int size,int search){
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if(array[i] == search)
            count++;
    }
    return count;
}

void bubble_sort(int** array,int size){
    int* cur = *array;
    for (int i = 0; i < size; i++)
        for (int j = i; j < size; j++)
            if(cur[i] < cur[j])
                swap(&cur[i],&cur[j]);
}

void selection_sort(int** array, int size) { 
    int* arr = *array;
    int min_idx = 0;
    for (int i = 0; i < size-1; i++) 
    { 
        min_idx = i; 
        for (int j = i+1; j < size; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j;   
        swap(&arr[min_idx], &arr[i]); 
    } 
}

void insertion_sort(int** array, int size) {
    int* arr = *array;
    int key = 0;
    int j = 0;
    for (int i = 1; i < size; i++) { 
        key = arr[i]; 
        j = i - 1;   
        while (j >= 0 && arr[j] > key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    } 
} 

void test_algo(char* func_name,void(*sort)(int**,int)){
   int* randoms[3],*ascendings[3],*increasings[3];
   int** all_array[] = {randoms,ascendings,increasings};
   for (int i = 0; i < 3; i++)
   {
      randoms[i] = create_random_array((int)pow(10,i+2));
      ascendings[i] = create_sorted_array((int)pow(10,i+2),ASCENDING);
      increasings[i] = create_sorted_array((int)pow(10,i+2),INCREASING);
   }
   clock_t start = clock();   
   for (int i = 0; i < 3; i++)
       for (int j = 0; j < 3; ++j){
          sort(&all_array[i][j],(int)pow(10,j+2));
          free(all_array[i][j]);
          }
   clock_t stop = clock();
   double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
   printf("Time elapsed for %s in ms: %.5f\n", func_name,elapsed);
}

int partition (int** array, int low, int high) { 
    int* arr = *array;
    int pivot = arr[high];
    int i = (low - 1);
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if (arr[j] < pivot) 
        {
            i++;
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  
void quick_sort(int** array, int low, int high) {
    int* arr = *array;
    if (low < high) 
    { 
        int pi = partition(array, low, high);   
        quick_sort(array, low, pi - 1); 
        quick_sort(array, pi + 1, high); 
    } 
}

void quick_sort_for_test(int** array,int size){
    quick_sort(array,0,size);
}

void merge(int* arr, int l, int m, int r) { 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0;
    j = 0;
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
void merge_sort(int arr[], int l, int r) { 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
        merge_sort(arr, l, m); 
        merge_sort(arr, m+1, r); 
        merge(arr, l, m, r); 
    } 
} 

void merge_sort_for_test(int** array,int size){
    merge_sort(*array,0,size);
}

int get_max(int* array, int size){
  int max = array[0];
  for (int i = 1; i < size; i++)
    if (array[i] > max)
      max = array[i];
  return max;
}

void bucket_sort(int** array, int size){
    int* ar = *array;
    int bucket[size];
    int max = get_max(ar, size);
    for (int i = 0; i <= max; i++)
      bucket[i] = 0;
    for (int i = 0; i < size; i++)
      bucket[ar[i]]++;
    
    for (int i = 0, j = 0; i <= max; i++)
    {
      while (bucket[i] > 0)
      {
        ar[j++] = i;
        bucket[i]--;
      }
    }
}

void shell_sort(int** array, int n) { 
    int* arr = *array;
    for (int gap = n/2; gap > 0; gap /= 2) 
    { 
        for (int i = gap; i < n; i += 1) 
        { 
            int temp = arr[i]; 
            int j;             
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
                arr[j] = arr[j - gap]; 
            arr[j] = temp; 
        } 
    } 
} 