/*
  s76905 beleg für Internetsicherheit
*/
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if (!(ctx = EVP_CIPHER_CTX_new()))
    handleErrors();

  /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
  if (1 != EVP_DecryptInit_ex(ctx, EVP_camellia_256_cfb1(), NULL, key, iv))
    handleErrors();

  /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
  if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
  if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
    handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}

int brutforce_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
                      unsigned char *iv, unsigned char *plaintext)
{
  for (size_t i = 0; i < 256; i++)
  {
    key[11] = (char)i;
    brutforce_decrypt(ciphertext, ciphertext_len, key, iv,
                      plaintext);
    if (plaintext[0] == '%' || plaintext[0] == 'P' || plaintext[0] == 'D' || plaintext[0] == 'F')
    {
      printf("found\n");
      break;
    }
  }
}

int main(void)
{
  FILE *keyFile;
  char *buffer;
  size_t result = 0;

  keyFile = fopen("s76905-source-key-corrupt.bin", "rb");
  if (keyFile == NULL)
  {
    fputs("File error", stderr);
    exit(1);
  }

  /* A 256 bit key */
  unsigned char *key = (unsigned char *)malloc(sizeof(char) * 32);
  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)malloc(sizeof(char) * 16);
  if (key == NULL || key == NULL)
  {
    fputs("Memory error", stderr);
    exit(2);
  }

  // copy the file into the keys:
  result += fread(buffer, 1, 32, keyFile);
  result += fread(buffer, 1, 16, keyFile);
  fclose(keyFile);
  if (result != 48)
  {
    fputs("Reading error", stderr);
    exit(3);
  }

  // Reading size of file
  FILE *cipherFile = fopen("s76905-source-cipher.bin", "r+");
  if (cipherFile == NULL)
    return;
  fseek(cipherFile, 0, SEEK_END);
  long int size = ftell(cipherFile);
  rewind(cipherFile);
  unsigned char *ciphertext = (unsigned char *)malloc(size);
  unsigned char *decryptedtext = (unsigned char *)malloc(size);
  int bytes_read = fread(ciphertext, sizeof(unsigned char), size, cipherFile);
  fclose(cipherFile);

  int decryptedtext_len, ciphertext_len;

  /* Decrypt the ciphertext */
  decryptedtext_len = brutforce_decrypt(ciphertext, ciphertext_len, key, iv,
                                        decryptedtext);

  cipherFile = fopen("output.pdf", "w+");
  write(decryptedtext, sizeof(unsigned char), size, cipherFile);
  fclose(cipherFile);

  // terminate
  free(buffer);
  free(ciphertext);
  free(decryptedtext);

  return 0;
}