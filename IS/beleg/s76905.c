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

int decrypt(unsigned char ciphertext[], int ciphertext_len, unsigned char key[],
            unsigned char iv[], unsigned char plaintext[])
{
  printf("init vars");
  EVP_CIPHER_CTX *ctx;
  int len;
  int plaintext_len;
  /* Load the human readable error strings for libcrypto */
  ERR_load_crypto_strings();

  printf("init context\n");
  /* Create and initialise the context */
  if (!(ctx = EVP_CIPHER_CTX_new()))
    handleErrors();

  printf("decrypt init\n");
  /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
  if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  printf("decrypt update\n");
  /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
  if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  printf("decrypt final\n");
  /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
  if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
    handleErrors();
  plaintext_len += len;

  printf("decrypt clean up\n");
  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);
  /* Removes all digests and ciphers */
  EVP_cleanup();
  /* if you omit the next, a small leak may be left when you make use of the BIO (low level API) for e.g. base64 transformations */
  CRYPTO_cleanup_all_ex_data();
  /* Remove error strings */
  ERR_free_strings();

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
    if (plaintext[0] == '%' || plaintext[1] == 'P' || plaintext[2] == 'D' || plaintext[3] == 'F')
    {
      printf("\n\nFound %PDF in decrypted file!\n\n");
      return len;
    }
  }
}

int main(void)
{
  printf("start main\n");
  FILE *keyFile;
  size_t result = 0;

  printf("reading keys out of a file\n");
  keyFile = fopen("s76905-source-key-corrupt.bin", "rb");
  //keyFile = fopen("s76905-source-key-corrupt-test.bin", "rb");
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
  printf("key: %s legth: %d\n", key, strlen(key));
  printf("iv: %s legth: %d\n", iv, strlen(iv));

  printf("reading cipher text out of a file\n");
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

  printf("saving decrypted text\n");
  cipherFile = fopen("output.pdf", "w+");
  fwrite(decryptedtext, sizeof(unsigned char), decryptedtext_len, cipherFile);
  fclose(cipherFile);

  printf("exit\n");
  return 0;
}
