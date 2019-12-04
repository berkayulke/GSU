#include <time.h>
#include <stdio.h>
#include "sort.h"
#include <math.h>

void swap_double(double *x, double *y)
{
   double temp = *x;
   *x = *y;
   *y = temp;
}

void swap_string(char *x, char *y)
{
   char *temp = x;
   x = y;
   y = temp;
}
void sort_two_arrays(double* main_ar,char** char_ar,int size){
   for (int i = 0; i < size; i++)
   {
      for (int j = i; j < size; j++)
      {
         if(main_ar[i] < main_ar[j])
            swap_double(&main_ar[i],&main_ar[j]);
            swap_string(char_ar[i],char_ar[j]);
      }
      
   }
   
}

int main()
{
   char *names[] = {
       "Bubble Sort   ",
       "Selection Sort",
       "Insertion Sort",
       "Quick Sort    ",
       "Merge Sort    ",
       "Bucket Sort   ",
       "Shell Sort    "};
   void *funcs[] = {
       bubble_sort,
       selection_sort,
       insertion_sort,
       quick_sort_for_test,
       merge_sort_for_test,
       bucket_sort,
       shell_sort};

   double res[6];
   for (int i = 0; i < 6; i++)
   {
      res[i] = test_algo(names[i], funcs[i]);
   }

   sort_two_arrays(res,names,6);
   for (int i = 0; i < 6; i++)
   {
      printf("%i - %s\t with time: %lf\n",i+1,names[5-i],res[5-i]);
   }
   

   return 0;
}