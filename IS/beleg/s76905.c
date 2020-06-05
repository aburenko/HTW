/*
  s76905 beleg für Internetsicherheit
*/
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

void err_exit(void)
{
  printf("%s\n", ERR_error_string(ERR_get_error(), NULL));

  ERR_free_strings();
  exit(EXIT_FAILURE);
}

// static char *pt(unsigned char *md)
// {
//   int i;
//   static char buf[16];
//   for (i = 0; i < 16; i++)
//   {
//     // write as hexadecimal to buf
//     sprintf(&(buf[i * 2]), "%02x", md[i]);
//   }
//   return (buf);
// }

// unsigned char *md4_hash(unsigned char plaintext[])
// {
//   printf("creating md4 hash");
//   FILE *fin;
//   long filesize;

//   EVP_MD_CTX c;
//   unsigned char md = malloc(sizeof(unsigned char) * 16);

//   ERR_load_crypto_strings();
//   EVP_MD_CTX_init(&c);

//   if ((EVP_DigestInit(&c, EVP_md4())) == 0)
//   {
//     err_exit();
//   }
//   if ((EVP_DigestUpdate(&c, plaintext, filesize)) == 0)
//   {
//     err_exit();
//   }
//   if ((EVP_DigestFinal(&c, md, NULL)) == 0)
//   {
//     err_exit();
//   }

//   // print as hexadecimal
//   printf("hash was %s\n", pt(md));

//   // clean ups
//   EVP_MD_CTX_cleanup(&c);
//   ERR_free_strings();

//   return md;
// }

void clean_up()
{
  /* Removes all digests and ciphers */
  EVP_cleanup();
  /* if you omit the next, a small leak may be left when you make use of the BIO (low level API) for e.g. base64 transformations */
  CRYPTO_cleanup_all_ex_data();
  /* Remove error strings */
  ERR_free_strings();
}

int decrypt(unsigned char ciphertext[], int ciphertext_len, unsigned char key[],
            unsigned char iv[], unsigned char plaintext[])
{
  printf("init vars");
  EVP_CIPHER_CTX *ctx;
  int len;
  int plaintext_len;
  /* Load the human readable error strings for libcrypto */
  ERR_load_crypto_strings();

  /* Create and initialise the context */
  if (!(ctx = EVP_CIPHER_CTX_new()))
    handleErrors();

  // printf("decrypt init\n");
  if (1 != EVP_DecryptInit_ex(ctx, EVP_camellia_256_cfb1(), NULL, key, iv))
    handleErrors();

  printf("decrypt update\n");
  if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  printf("decrypt final\n");
  if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
  {
    plaintext_len = -1;
    printf("decryption failed\n");
  }
  else
  {
    plaintext_len += len;
  }

  printf("decrypt clean up\n");
  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}

int brutforce_decrypt(unsigned char ciphertext[], int ciphertext_len, unsigned char key[],
                      unsigned char iv[], unsigned char plaintext[])
{
  printf("starting brutforce\n");
  for (int i = 0; i < 256; i++)
  {
    printf("bf value is: %d\n", i);
    key[11] = (char)i;

    int len = decrypt(ciphertext, ciphertext_len, key, iv,
                      plaintext);
    printf("starts with: ");
    for (int j = 0; j < 5; j++)
    {
      printf("%02x", plaintext[j]);
    }
    printf("\n");
    if (len != -1 && plaintext[0] == '%' && plaintext[1] == 'P' && plaintext[2] == 'D' && plaintext[3] == 'F')
    {
      printf("\n\nFound %PDF in decrypted file!\n\n");
      return len;
    }
    clean_up();
  }
  return -1;
}

int main(void)
{
  printf("start main\n");
  FILE *keyFile;
  size_t result = 0;

  printf("reading keys out of a file\n");
  keyFile = fopen("s76905-source-key-corrupt.bin", "rb");
  if (keyFile == NULL)
  {
    fputs("File error", stderr);
    exit(1);
  }

  /* A 256 bit key */
  unsigned char key[32];
  /* A 128 bit IV */
  unsigned char iv[16];

  // copy the file into the keys:
  result += fread(key, 1, 32, keyFile);
  result += fread(iv, 1, 16, keyFile);
  fclose(keyFile);
  if (result != 48)
  {
    fputs("Reading error", stderr);
    exit(2);
  }
  printf("key: ");
  for (int i = 0; i < 32; i++)
  {
    printf("%02x", key[i]);
  }
  printf("\niv: ");
  for (int i = 0; i < 16; i++)
  {
    printf("%02x", iv[i]);
  }
  printf("\nreading cipher text out of a file\n");
  // Reading size of file
  FILE *cipherFile = fopen("s76905-source-cipher.bin", "r+");
  if (cipherFile == NULL)
  {
    fputs("Reading error", stderr);
    exit(3);
  }
  fseek(cipherFile, 0, SEEK_END);
  long int size = ftell(cipherFile);
  rewind(cipherFile);
  unsigned char ciphertext[size];
  unsigned char decryptedtext[size];
  int bytes_read = fread(ciphertext, sizeof(unsigned char), size, cipherFile);
  if (bytes_read != size)
  {
    fputs("Reading error", stderr);
    exit(4);
  }
  fclose(cipherFile);

  int decryptedtext_len, ciphertext_len;

  /* Decrypt the ciphertext */
  decryptedtext_len = brutforce_decrypt(ciphertext, ciphertext_len, key, iv,
                                        decryptedtext);

  if (decryptedtext_len == -1)
  {
    printf("\nno match for %PDF found\n");
    exit(5);
  }
  printf("\nsaving decrypted text\n");
  cipherFile = fopen("output.pdf", "w+");
  fwrite(decryptedtext, sizeof(unsigned char), decryptedtext_len, cipherFile);
  fclose(cipherFile);

  // unsigned char *md4Hash = md4_hash(decryptedtext);

  printf("exit\n");
  return 0;
}
