#include <time.h>
#include <stdio.h>
#include "crypto.h"
#include <math.h>

int main(int argc, char const *argv[])
{
   char input[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
   int p = 2, q = 13, str_size = 26;
   
   rsa_encoder(input, p, q, str_size);

   printf("encoded -> %s\n", input);

   rsa_decoder(input, p, q, str_size);

   char expected[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
   for (int i = 0; i < str_size; i++)
      if (expected[i] != input[i])
         printf("expected -> %c got -> %c\n", expected[i], input[i]);

   return 0;
}
