#include <time.h>
#include <stdio.h>
#include "crypto.h"
#include <math.h>

int main(int argc, char const *argv[])
{
   char input[128];
   printf("Metin giriniz: \n");
   scanf("%s", input);

   matrix_encoder(input);
   printf("encoded -> %s\n", input);

   matrix_decoder(input);
   printf("decoded -> %s\n", input);

   return 0;
}
