#include <time.h>
#include <stdio.h>
#include "crypto.h"
#include <math.h>

int main(int argc, char const *argv[])
{
   char input[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
   char expected[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
   int p = 2, q = 13, str_size = 26;
   ceaser_encoder(input, 2);
   printf("ceaser encoded -> %s\n", input);
   ceaser_decoder(input, 2);
   printf("ceaser decoded -> %s\n\n", input);

   vigenere_encoder(input, "AYUSH");
   printf("vigenere encoded -> %s\n", input);
   vigenere_decoder(input, "AYUSH");
   printf("vigenere decoded -> %s\n\n", input);
   
   matrix_encoder(input);
   printf("matrix encoded -> %s\n", input);
   matrix_decoder(input);
   printf("matrix decoded -> %s\n\n", input);

   rsa_encoder(input, p, q, str_size);
   printf("rsa encoded -> %s\n", input);
   rsa_decoder(input, p, q, str_size);
   printf("rsa decoded -> %s\n\n", input);

   return 0;
}
