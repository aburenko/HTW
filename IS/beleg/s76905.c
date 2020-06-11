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

static char *pt(unsigned char *md)
{
  int i;
  static char buf[16];
  for (i = 0; i < 16; i++)
  {
    // write as hexadecimal to buf
    sprintf(&(buf[i * 2]), "%02x", md[i]);
  }
  return (buf);
}

unsigned char *md4_hash(unsigned char text[], int len)
{
  printf("\ncreating md4 hash\n");
  EVP_MD_CTX c;
  unsigned char *md = malloc(sizeof(unsigned char) * 16);

  ERR_load_crypto_strings();
  EVP_MD_CTX_init(&c);

  if ((EVP_DigestInit(&c, EVP_md4())) == 0)
  {
    err_exit();
  }
  if ((EVP_DigestUpdate(&c, text, len)) == 0)
  {
    err_exit();
  }
  if ((EVP_DigestFinal(&c, md, NULL)) == 0)
  {
    err_exit();
  }

  // print as hexadecimal
  printf("hash was %s\n", pt(md));

  // clean ups
  EVP_MD_CTX_cleanup(&c);
  ERR_free_strings();

  return md;
}

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
            unsigned char iv[], unsigned char plaintext[], const EVP_CIPHER *type)
{
  printf("init vars\n");
  EVP_CIPHER_CTX *ctx;
  int len;
  int plaintext_len;
  /* Load the human readable error strings for libcrypto */
  ERR_load_crypto_strings();

  /* Create and initialise the context */
  if (!(ctx = EVP_CIPHER_CTX_new()))
    handleErrors();

  // printf("decrypt init\n");
  if (1 != EVP_DecryptInit_ex(ctx, type, NULL, key, iv))
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
                      plaintext, EVP_camellia_256_cfb1());
    printf("len was: %d. Starts with: ", len);
    for (int j = 0; j < 5; j++)
    {
      printf("%02x", plaintext[j]);
    }
    printf("\n");
    if (len != -1 && plaintext[0] == '%' && plaintext[1] == 'P' && plaintext[2] == 'D' && plaintext[3] == 'F')
    {
      printf("\n\nFound %%PDF in decrypted file!\n\n");
      return len;
    }
    clean_up();
  }
  return -1;
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;
  int ciphertext_len;

  /* Create and initialise the context */
  if (!(ctx = EVP_CIPHER_CTX_new()))
    handleErrors();

  if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_192_ofb(), NULL, key, iv))
    handleErrors();

  if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    handleErrors();
  ciphertext_len += len;

  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

void getKeys(char *file, unsigned char *key,
             unsigned char *iv, int sizeKey)
{
  FILE *keyFile;
  size_t result = 0;
  printf("reading keys out of a %s\n", file);
  keyFile = fopen(file, "rb");
  if (keyFile == NULL)
  {
    fputs("File error", stderr);
    exit(1);
  }

  // copy the file into the keys:
  result += fread(key, 1, sizeKey, keyFile);
  result += fread(iv, 1, 16, keyFile);
  fclose(keyFile);
  if (result != sizeKey + 16)
  {
    fputs("Reading error", stderr);
    exit(2);
  }
  printf("key: ");
  for (int i = 0; i < sizeKey; i++)
  {
    printf("%02x", key[i]);
  }
  printf("\niv: ");
  for (int i = 0; i < 16; i++)
  {
    printf("%02x", iv[i]);
  }
  printf("\n");
}

int main(void)
{
  printf("start main\n");

  /* A 256 bit key */
  unsigned char key[32];
  /* A 128 bit IV */
  unsigned char iv[16];
  getKeys("s76905-source-key-corrupt.bin", key, iv, 32);

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

  int ciphertext_len = size;
  int decryptedtext_len = 0;

  /* Decrypt the ciphertext */
  decryptedtext_len = brutforce_decrypt(ciphertext, ciphertext_len, key, iv,
                                        decryptedtext);

  if (decryptedtext_len == -1)
  {
    printf("\nno match for %%PDF found\n");
    exit(5);
  }

  /* save decrypted pdf file */
  // printf("\nsaving decrypted text\n");
  // cipherFile = fopen("output.pdf", "w+");
  // fwrite(decryptedtext, sizeof(unsigned char), decryptedtext_len, cipherFile);
  // fclose(cipherFile);

  unsigned char *md4Hash = md4_hash(decryptedtext, decryptedtext_len);
  /* concatenate decrypted text with hash */
  int dest_size = size + 16;
  unsigned char hashedtext[dest_size];
  strcpy(hashedtext, decryptedtext);
  strcat(hashedtext, md4Hash);
  /* Encrypt the plaintext with hash */
  unsigned char keyAes[24];
  unsigned char ivAes[16];
  getKeys("s76905-dest-key.bin", keyAes, ivAes, 24);
  int encrypted_len = 0;
  unsigned char encryptedhashedtext[dest_size];
  encrypted_len = encrypt(hashedtext, dest_size, keyAes, ivAes,
                          encryptedhashedtext);

  printf("len was: %d. Starts with: ", encrypted_len);
  for (int j = 0; j < 5; j++)
  {
    printf("%02x", encryptedhashedtext[j]);
  }
  printf("\n");

  // test
  /* Decrypt the ciphertext */
  printf("start test\n");
  unsigned char testtext[dest_size];
  int testtext_len = decrypt(encryptedhashedtext, encrypted_len, keyAes, ivAes,
                             testtext, EVP_aes_192_ofb());
  if (testtext_len != dest_size)
  {
    printf("test: size error\n");
    exit(7);
  }
  if (testtext[0] != '%' || testtext[1] != 'P' || testtext[2] != 'D' || testtext[3] != 'F')
  {
    printf("test: pdf not found error\n");
    exit(7);
  }
  if (testtext[dest_size - 2] != md4Hash[14] || testtext[dest_size - 1] != md4Hash[15])
  {
    for (int j = 2; j > 0; j--)
    {
      printf("%02x", plaintext[dest_size - 1 - j]);
    }
    printf("test: hash not found error\n");
    exit(7);
  }
  printf("end test\n");

  /* save encrypted pdf with hash */
  printf("\nsaving enrypted text + hash\n");
  cipherFile = fopen("s76905-dest-cipher.bin", "w+");
  fwrite(encryptedhashedtext, sizeof(unsigned char), encrypted_len, cipherFile);
  fclose(cipherFile);

  printf("exit\n");
  return 0;
}
