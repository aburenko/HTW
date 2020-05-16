/*
  bf-tea.c

  Solution to collection 4, assignment 1
  - TEA implementation according to 
    http://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define KNOWN "xdfg19rtbg38:+h"
// loesung 60 entspricht >

char charBuffer[8] = "xxxxxxxx";

void decrypt (uint32_t* v, uint32_t* k) {
  uint32_t v0=v[0], v1=v[1], sum=0xC6EF3720, i;  /* set up */
  uint32_t delta=0x9e3779b9;            /* a key schedule constant */
  unsigned long k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
  for (i=0; i<32; i++) {                      /* basic cycle start */
    v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
    sum -= delta;                                   
  }                                              /* end cycle */
  v[0]=v0; v[1]=v1;
}

char getLastChar(long long value)
{
    return (char)((value >> 8 * 7) & 0XFF);
}

int main(int argc, char* argv[])
{
  FILE *fin, *fout;
  char key[16] = KNOWN;
  unsigned long long bl;
  char outfilename[64];
  int lastbyte;

  if (argc != 2) {
    printf("Usage: %s <chiffrefile>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  fin = fopen(argv[1], "r");
  if (fin == NULL) {
    perror("fopen, infile");
    exit(EXIT_FAILURE);
  }

  /*
    Master Brute-Force-Loop
  */
  for (lastbyte=0; lastbyte<256; lastbyte++){

    rewind(fin);
    sprintf(outfilename, "%s%03d", "outfile", lastbyte);
    fout = fopen(outfilename, "w");
    if (fout == NULL) {
      perror("fopen, outfile");
    }

    key[15] = lastbyte;
    /* 'decode' with key */
    while(!feof(fin)) {
      fread(&bl, 8, 1, fin);
      decrypt((uint32_t*) &bl, (uint32_t*) key);
      fwrite(&bl, 8, 1, fout);
    }
    //printf("last char was: %c\n", getLastChar(bl));
    if (isdigit(getLastChar(bl))) {
        printf("digit was on %d \n", lastbyte);
    }
    fclose(fout);
  }

  fclose(fin);
  exit(EXIT_SUCCESS);
}
