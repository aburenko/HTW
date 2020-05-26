#include <stdio.h>
#include <stdlib.h>

#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/err.h>

static char *pt(unsigned char *md)
{
  int i;
  static char buf[80];
  
  for (i=0; i<SHA_DIGEST_LENGTH; i++) {
    // write as hexadecimal to buf
    sprintf(&(buf[i*2]), "%02x", md[i]);
  }
  return(buf);
}

void err_exit(void)
{
  printf("%s\n", ERR_error_string(ERR_get_error(), NULL));

  ERR_free_strings();
  exit(EXIT_FAILURE);
}
 // CALL WITH -lcrypto !!!
int main(int argc, char *argv[])
{
  FILE *fin;
  long filesize;
  char *buf;

  // z ist variable that holds "context"
  EVP_MD_CTX c;
  unsigned char md[SHA_DIGEST_LENGTH];
  
  /* Load the human readable error strings for libcrypto */
  ERR_load_crypto_strings();

  EVP_MD_CTX_init(&c);  /* not necessary when not using _ex */

  if (argc != 2) {
    printf("Usage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  // open and calculate size
  if ((fin = fopen(argv[1], "r")) == NULL){
    printf("Error opening %s.\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  fseek(fin, 0L, SEEK_END);
  filesize = ftell(fin);
  rewind(fin);
  
  // read out the file in a buf
  if (!(buf=malloc(filesize))) {
    printf("Memory exhausted. Stop.\n");
    exit(EXIT_FAILURE);
  }
  fread(buf, filesize, 1, fin);
  fclose(fin);

  if ((EVP_DigestInit(&c, EVP_sha1())) == 0) {
    err_exit();
  }
  if ((EVP_DigestUpdate(&c, buf, filesize)) == 0) {
    err_exit();
  }
  if ((EVP_DigestFinal(&c, md, NULL)) == 0) {
    err_exit();
  }

  // print as hexadecimal
  printf("%s\n", pt(md));

  // clean ups
  EVP_MD_CTX_cleanup(&c);
  free(buf);
  ERR_free_strings();

  exit(EXIT_SUCCESS);
}

