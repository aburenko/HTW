#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int freq[26];

int main(int argc, char* argv[])
{
  FILE *fin;
  int in, c;

  if (argc != 2) {
    printf("Usage: %s <textfile>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  fin = fopen(argv[1], "r");
  if (fin == NULL) {
    perror("opening text file");
    exit(EXIT_FAILURE);
  }
  while (!feof(fin)) {
    in = fgetc(fin);
    if (isalpha(in)) {
      freq[toupper(in)-'A']++;
    }
  }
  fclose(fin);

  /* output char frequency */
  for (c=0; c<26; c++) {
    printf("%c : %d\n", c+'A', freq[c]);
  } 
  exit(EXIT_SUCCESS);
}
