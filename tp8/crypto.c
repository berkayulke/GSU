#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "crypto.h"

//karesi num'dan büyük olan en küçük sayıyı döndürür
int nearest_square(int num)
{
    int i = 1;
    while (i * i < num)
        ++i;
    return i;
}

void ceaser_encoder(char *str, int move)
{
    int size = strlen(str);
    for (int i = 0; i < size; i++)
        str[i] += move;
}

void ceaser_decoder(char *str, int move)
{
    int size = strlen(str);
    for (int i = 0; i < size; i++)
        str[i] -= move;
}

char vigenere_table(char row, char column, int case_type)
{
    int alp_size = 'A' - 'Z' - 1;
    if (case_type == UPPER)
    {
        int row_ind = (int)(row - 'A');
        int col_ind = (int)(column - 'A');

        return (row_ind + col_ind) % alp_size + 'A';
    }

    int row_ind = (int)(row - 'a');
    int col_ind = (int)(column - 'a');

    return (row_ind + col_ind) % alp_size + 'a';
}

void vigenere_encoder(char *str, char *key)
{
    int text_size = strlen(str);
    int key_size = strlen(key);
    char cipher_text[text_size];

    for (int i = 0; i < text_size; i++)
        cipher_text[i] = key[i % key_size];

    for (int i = 0; i < text_size; i++)
    {
        char column = cipher_text[i];
        char row = str[i];
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = vigenere_table(row, column, UPPER);
        else
            str[i] = vigenere_table(row, column, DOWN);
    }
}

void vigenere_decoder(char *str, char *key)
{
    int text_size = strlen(str);
    int key_size = strlen(key);

    for (int i = 0; i < text_size; i++)
    {
        str[i] = (str[i] - key[i % key_size] + 26) % 26 + 'a';
    }
}

void matrix_encoder(char *str)
{
    int str_size = strlen(str);
    int mtr_size = nearest_square(str_size);

    char **matrix = malloc(mtr_size * sizeof(char *));
    for (int i = 0; i < mtr_size; i++)
        matrix[i] = malloc(mtr_size * sizeof(char));

    for (int i = 0; i < str_size; i++)
        matrix[i / mtr_size][i % mtr_size] = str[i];

    //matrixi kullan
    for (int mtr_i = 0, str_i = 0; str_i < str_size; mtr_i++)
    {
        if (!matrix[mtr_i % mtr_size][mtr_i / mtr_size])
            continue;
        str[str_i++] = matrix[mtr_i % mtr_size][mtr_i / mtr_size];
    }

    for (int i = 0; i < mtr_size; i++)
        free(matrix[i]);
    free(matrix);
}

void matrix_decoder(char *str)
{
    int str_size = strlen(str);
    int mtr_size = nearest_square(str_size);
    if (mtr_size * mtr_size == str_size)
    {
        //kare gelirse bi daha yap
        matrix_encoder(str);
        return;
    }

    char **matrix = malloc(mtr_size * sizeof(char *));
    for (int i = 0; i < mtr_size; i++)
        matrix[i] = malloc(mtr_size * sizeof(char));

    for (int i = 0; i < str_size; i++)
    {
        int ind1 = i / mtr_size;
        int ind2 = i % mtr_size;
        matrix[ind1][ind2] = str[i];
    }
    //print
    for (int i = 0; i < mtr_size; i++)
    {
        for (int j = 0; j < mtr_size; j++)
            printf("%c", matrix[i][j]);
        printf("\n");
    }
}