/*
  s76905 beleg für Internetsicherheit
*/
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int brutforce_decrypt(unsigned char key[])
{
  printf("starting brutforce\n");
  int i = 65;
  printf("bf value is: %d\n", i);
  key[11] = (char)i;
  printf(" value : %s\n", key);
}

int main(void)
{
  printf("start main\n");

  unsigned char *keyP = (unsigned char *)malloc(sizeof(char) * 32);

  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)"0123456789012345";

  /* Message to be encrypted */
  unsigned char *ciphertext =
      (unsigned char *)"The quick brown fox jumps over the lazy dog";

  keyP = (unsigned char *)"01234567890123456789012345678901";
  unsigned char key[32];
  strcpy(key, keyP);

  /* Decrypt the ciphertext */
  brutforce_decrypt(key);

  return 0;
}
