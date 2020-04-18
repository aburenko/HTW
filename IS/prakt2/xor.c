#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
  FILE *fin, *fout, *fkey;
  int chin, chkey;

  if (argc != 4) {
    printf("Usage: %s <keyfile> <plaintextfile> <cipherfile>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if (!(fkey=fopen(argv[1], "r"))) {
    perror("Key file");
    exit(EXIT_FAILURE);
  }
  if (!(fin=fopen(argv[2], "r"))) {
    perror("Plaintext file");
    exit(EXIT_FAILURE);
  }
  if (!(fout=fopen(argv[3], "w"))) {
    perror("Cipher file");
    exit(EXIT_FAILURE);
  }

  /* encryption loop */
  chin = fgetc(fin);
  while (!feof(fin)) {
    chkey = fgetc(fkey);
    if (feof(fkey)) {
      rewind(fkey);
      chkey = fgetc(fkey);
    }
    chin ^= chkey;
    fputc(chin, fout);
    chin = fgetc(fin);
  }

  /* epilogue */
  fclose(fkey);
  fclose(fout);
  fclose(fin);
  exit(EXIT_SUCCESS);
}
