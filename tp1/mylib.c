#include <stdlib.h>
#include "mylib.h"
#include <math.h>
#include <stdio.h>
#include <time.h>

int isLetter(char c)
{
  //printf("%c\n",c);
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
  {
    return 1;
  }
  return 0;
}

int isDigit(char c)
{
  //printf("%c\n",c);
  if ((c >= '0' && c <= '9'))
  {
    return 1;
  }
  return 0;
}

int isEven(int value)
{
  if (value % 2 == 0)
    return 1;
  return 0;
}

int isPrime(int value)
{
  if (value == 1 || value == 0)
  {
    return 0;
  }
  for (int i = 2; i < value / 2; i++)
  {
    if (value % i == 0)
      return 0;
  }
  return 1;
}

int digitSum(int value)
{
  int sum = 0;
  if (value <= 9)
    return value;

  sum += value % 10;
  sum += digitSum(value / 10);
  return sum;
}
int reverseNumber(int value)
{
  int copy = value;
  if (value <= 9)
    return value;
  int first_digit = value % 10;
  int rest = value / 10;
  int digit_amount = 0;
  while (copy > 1)
  {
    copy /= 10;
    first_digit *= 10;
  }
  return first_digit + reverseNumber(rest);
}

char upperCase(char c)
{
  return c - ('a' - 'A');
}
char downCase(char c)
{
  return c + ('a' - 'A');
}

int isUpperCase(char c)
{
  if (c >= 'A' && c <= 'Z')
    return 1;
  return 0;
}

int factoriel(int value)
{
  if (value <= 1)
    return 1;
  else
    return value * factoriel(value - 1);
}

int power(int base, int degree)
{
  int res = 1;
  for (int i = 0; i < degree; i++)
  {
    res *= base;
  }
  return res;
}

int add(int value1, int value2)
{
  return value1 + value2;
}

float *findRoots(int a, int b, int c)
{
  int delta = 0;
  delta = pow(b, 2) - 4 * a * c;
  float *ar = malloc(2 * sizeof(float));
  ar[0] = (-b + sqrt(delta)) / 2;
  ar[1] = (-b - sqrt(delta)) / 2;
  return ar;
}

void hailstoneNumbers(int value)
{
  int cur_num = value;
  while (cur_num != 1)
  {
    printf("%i ", cur_num);
    if (cur_num % 2 == 0)
    {
      cur_num /= 2;
    }
    else
    {
      cur_num = 3 * cur_num + 1;
    }
  }
  printf("1 4 2 1...\n");
}

int isPalindromeNumber(int value)
{
  int reverse = reverseNumber(value);
  if (reverse == value)
    return 1;
  return 0;
}

int isPalindromeText(char *c, int size)
{
  for (int i = 0; i < size / 2; i++)
  {
    if (c[i] != c[size - i - 1])
      return 0;
  }
  return 1;
}

int isVowel(char c)
{
  char vowels[] = {'e', 'u', 'i', 'o', 'a'};
  for (int i = 0; i < 5; i++)
  {
    if (c == vowels[i] || c == (vowels[i]) + 'A' - 'a')
      return 1;
  }
  return 0;
}

int exist(int *arr, int size, int value)
{
  for (int i = 0; i < size; i++)
  {
    if (value == arr[i])
      return 1;
  }
  return 0;
}

int getIndex(int *arr, int size, int value)
{
  for (int i = 0; i < size; i++)
  {
    if (arr[i] == value)
      return i;
  }
  return -1;
}

int count(int *arr, int size, int value)
{
  int count = 0;
  for (int i = 0; i < size; i++)
  {
    if (arr[i] == value)
      count++;
  }
  return count;
}

int findMax(int *arr, int size)
{
  int max = arr[0];
  for (int i = 0; i < size; i++)
  {
    if (arr[i] > max)
      max = arr[i];
  }
  return max;
}

int findMax2(int *arr, int size)
{
  int max1 = arr[0];
  int max2 = arr[0];
  for (int i = 0; i < size; i++)
  {
    if (arr[i] > max1)
    {
      max2 = max1;
      max1 = arr[i];
    }
  }
  return max2;
}

int findMin(int *arr, int size)
{
  int min = arr[0];
  for (int i = 0; i < size; i++)
  {
    if (arr[i] < min)
      min = arr[i];
  }
  return min;
}

int findMin2(int *arr, int size)
{
  int min1 = arr[0];
  int min2 = arr[0];
  for (int i = 0; i < size; i++)
  {
    if (arr[i] < min1)
    {
      min2 = min1;
      min1 = arr[i];
    }
  }
  return min2;
}

int sumArray(int *arr, int size)
{
  int sum = 0;
  for (int i = 0; i < size; i++)
  {
    sum += arr[i];
  }
  return sum;
}

double averageArr(int *arr, int size)
{
  double av = 0.0;
  for (int i = 0; i < size; i++)
  {
    av += (double)arr[i];
  }
  return av / (double)size;
}

double deviationArr(int *arr, int size)
{
  double devi = 0.0;
  int mean = averageArr(arr, size);
  for (int i = 0; i < size; i++)
  {
    int current = arr[i];
    devi += ((double)current - mean) * ((double)current - mean);
  }
  return sqrt(devi / (double)size);
}

void printMatrix(int **matrix, int row, int column)
{
  for (int i = 0; i < row; i++)
  {
    {
      for (int j = 0; j < column; j++)
        printf("%i ", matrix[i][j]);
    }
    printf("\n");
  }
}

int **transposeMatrix(int **matrix, int row, int column)
{
  int **dest = malloc(column * sizeof(int *));
  for (int i = 0; i < column; i++)
  {
    dest[i] = malloc(row * sizeof(int));
  }

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      dest[j][i] = matrix[i][j];
    }
  }
  return dest;
}

int **fillMatrix(int **matrix, int row, int column)
{
  int **dest = malloc(column * sizeof(int *));
  for (int i = 0; i < column; i++)
  {
    dest[i] = malloc(row * sizeof(int));
  }
  for (int i = 0; i < row; i++)
  {
    {
      for (int j = 0; j < column; j++)
        dest[i][j] = 50 + rand() % 50;
    }
  }
  return dest;
}