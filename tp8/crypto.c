#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "crypto.h"

char upper_case(char c)
{
    if (c <= 'z' && c >= 'a')
        return c - 32;
    return c;
}

char fit(char c)
{
    return upper_case(c) - 'E';
}

char unfit(char c)
{
    return c + 'E';
}

//karesi num'dan büyük olan en küçük sayıyı döndürür
int nearest_square(int num)
{
    int r = sqrt(num);
    if (r * r == num)
        return r;
    return r + 1;
}

int is_prime(double num)
{
    if(num == 2)
        return 1;
    if (fmod(num, (double)2) == 0.0)
        return 0;
    for (double i = 3; i * i <= num; i += 2)
        if (fmod(num, i) == 0.0)
            return 0;
    return 1;
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

    //eğer kare matrix gelmezse sağ alltan başlayarak en alt sırayı -1 ile doldur
    //sonra sadece kalan boşluklara metni yerleştir
    //solda sağa oku
    //nasıl çalıştığı hakkında hiçbir fikrim yok
    char **matrix = malloc(mtr_size * sizeof(char *));
    for (int i = 0; i < mtr_size; i++)
        matrix[i] = malloc(mtr_size * sizeof(char));

    for (int i = 0; i < mtr_size * mtr_size - str_size; i++)
    {
        int ind1 = mtr_size - i / mtr_size - 1;
        int ind2 = mtr_size - i % mtr_size - 1;
        matrix[ind1][ind2] = -1;
    }
    for (int mtr_i = 0, str_i = 0; mtr_i < mtr_size * mtr_size; mtr_i++)
    {
        int ind1 = mtr_i % mtr_size;
        int ind2 = mtr_i / mtr_size;

        if (matrix[ind1][ind2] == -1)
            continue;
        matrix[ind1][ind2] = str[str_i++];
    }

    for (int mtr_i = 0, str_i = 0; mtr_i < mtr_size * mtr_size; mtr_i++)
    {
        int ind1 = mtr_i / mtr_size;
        int ind2 = mtr_i % mtr_size;

        if (matrix[ind1][ind2] == -1)
            continue;
        str[str_i++] = matrix[ind1][ind2];
    }
}

int gcd(int a, int b)
{
    if (!a)
        return b;
    if (!b)
        return a;
    if (a == b)
        return a;

    if (a > b)
        return gcd(a - b, b);
    return gcd(a, b - a);
}

int create_e_value(int totient)
{
    return 2;
    for (int i = 0; i < totient; i++)
        if (gcd(i, totient) == 1)
            return i;
}

int inverse_modulus(int a, int m)
{
    a = fmod(a, m);
    for (int x = 1; x < m; x++)
        if (fmod((a * x), m) == 1)
            return x;
}

void rsa_encoder(char *str, double p, double q, double size)
{
    if (!is_prime(p) || !is_prime(q))
    {
        printf("No Bueno\n");
        return;
    }

    double str_size = strlen(str);

    double n = p * q;
    double e = 2;
    double totient = (p - 1) * (q - 1);

    while (e < totient)
    {
        if (gcd(e, totient) == 1)
            break;
        e++;
    }
    double d = (1 + (2 * totient)) / e;

    for (int i = 0; i < size; i++)
    {
        // 0-32 arasına çek
        char inp = fit(str[i]);
        double c = pow((double)inp, e);
        c = fmod(c, n);
        str[i] = unfit(c);
    }
}

void rsa_decoder(char *str, double p, double q, double size)
{
    if (!is_prime(p) || !is_prime(q))
    {
        printf("No Bueno\n");
        return;
    }

    double str_size = strlen(str);

    double n = p * q;
    double e = 2;
    double totient = (p - 1) * (q - 1);

    while (e < totient)
    {
        if (gcd(e, totient) == 1)
            break;
        e++;
    }
    double d = (1 + (2 * totient)) / e;

    for (int i = 0; i < size; i++)
    {
        char inp = fit(str[i]);
        double c = pow(inp, e);
        c = fmod(c, n);
        str[i] = unfit(c);
    }
}