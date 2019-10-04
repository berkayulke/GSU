#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mylib.h"

int test_no = 1;

void tester(int expected, int reality)
{
    if (expected == reality)
    {
        printf("Test - %i passed\n", test_no);
        test_no++;
        return;
    }
    printf("Test - %i FAILED\n", test_no);
    printf("    expected = %i \n    got = %i\n", expected, reality);
    test_no++;
}

// to complile from terminal, run: gcc test.c mylib.c -o ApplicationName -lm
// to run the complied application, run: ./ApplicatioName

int main(void)
{
    // a remplir
    char low_case = 'c';
    char up_case = 'C';
    char low_vowel = 'e';
    char up_vowel = 'E';
    char false_char = '0';

    // Test 1
    tester(1, isLetter(low_case));
    tester(1, isLetter(up_case));
    tester(0, isLetter(false_char));

    //test 2
    tester(0, isDigit(up_case));
    tester(1, isDigit(false_char));

    //test 3
    tester(1, isEven(2));
    tester(0, isEven(1));

    //test 4
    tester(0, isPrime(1));
    tester(1, isPrime(13));

    //test 5
    tester(10, digitSum(1234));

    //test 6
    tester(4321, reverseNumber(1234));

    //test 7
    tester(up_case, upperCase(low_case));

    //test 8
    tester(low_case, downCase(up_case));

    //test 9
    tester(1, isUpperCase(up_case));
    tester(0, isUpperCase(low_case));

    //test 10
    tester(120, factoriel(5));

    //test 11
    tester(125, power(5, 3));

    //test 12
    tester(1 + 2, add(1, 2));

    //test 13
    float *test_13 = findRoots(1, 4, 4);
    tester(-2, test_13[0]);
    tester(-2, test_13[1]);

    //test 14
    printf("Hailstone Number beggining at 123: ");
    hailstoneNumbers(123);
    test_no++;

    //test 15
    tester(1, isPalindromeNumber(12321));
    tester(0, isPalindromeNumber(1232));

    //test 16
    tester(1, isPalindromeText("12321", 5));
    tester(0, isPalindromeText("1232", 4));

    //test 17
    tester(1, isVowel(low_vowel));
    tester(1, isVowel(up_vowel));
    tester(0, isVowel(low_case));
    tester(0, isVowel(up_case));

    //test 18
    int test_18[] = {1, 2, 3, 4};
    tester(1, exist(test_18, 4, 3));
    tester(0, exist(test_18, 4, 5));

    //test 19
    tester(0, getIndex(test_18, 4, 1));
    tester(3, getIndex(test_18, 4, 4));
    tester(-1, getIndex(test_18, 4, 5));

    //test 20
    int test_20[] = {1, 2, 3, 2, 2, 5};
    tester(1, count(test_20, 6, 1));
    tester(3, count(test_20, 6, 2));
    tester(0, count(test_20, 6, 6));

    //test 21
    int test_21[] = {1, 2, 3, 4, 5, 6, 0};
    tester(6, findMax(test_21, 7));

    //test 22
    tester(5, findMax2(test_21, 7));

    //test 23
    tester(0, findMin(test_21, 7));

    //test 24
    tester(1, findMin2(test_21, 7));

    //test 25
    int test_25[] = {1, 3, 5, 2};
    tester(11, sumArray(test_25, 4));

    //test 26
    int test_26[] = {1, 5, 2, 4};
    tester(3, (int)averageArr(test_26, 4));

    //test 27
    int test_27[] = {6, 2, 3, 1};
    double dev = deviationArr(test_27, 4);
    //double'ları kıyaslarken hata aldım o yüzden böyle kontrol ediyorum
    if (fabs(1.870829 - dev) < 0.00001)
    {
        printf("Test - %i passed\n", test_no);
        test_no++;
    }
    else
    {
        printf("Test - %i FAILED\n", test_no);
        test_no++;
    }
    test_no++;

    //test 28
    int **matrix = (int **)malloc(3 * sizeof(int *));
    for (int i = 0; i < 3; i++)
    {
        matrix[i] = malloc(4 * sizeof(int));
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = (2 * i + 1) * (3 * j + 1);
        }
    }
    printf("\nMatrix:\n");
    printMatrix(matrix, 3, 4);

    //test 29
    int **transpose = transposeMatrix(matrix, 3, 4);
    printf("\nTranspose:\n");
    printMatrix(transpose, 4, 3);

    //test 30
    int **filled = fillMatrix(matrix, 3, 4);
    printf("\nFilled:\n");
    printMatrix(filled, 3, 4);
    return 0;
}
