#include <time.h>
#include <stdio.h>
#include "sort.h"
#include <math.h>
int main(){
   test_algo("Bubble Sort   ",bubble_sort);
   test_algo("Selection Sort",selection_sort);
   test_algo("Insertion Sort",insertion_sort);
   test_algo("Quick Sort    ",quick_sort_for_test);
   test_algo("Merge Sort    ",merge_sort_for_test);
   test_algo("Bucket Sort   ",bucket_sort);
   test_algo("Shell Sort    ",shell_sort);
}