#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef __CRYPTO_H_
#define __CRYPTO_H_

enum case_type
{
    UPPER,
    DOWN
};

int nearest_square(int num);

void ceaser_encoder(char *str, int move);
void ceaser_decoder(char *str, int move);

char vigenere_table(char row, char column, int case_type);
void vigenere_encoder(char *str, char *key);
void vigenere_decoder(char *str, char *key);

void matrix_encoder(char *str);
void matrix_decoder(char *str);

#endif