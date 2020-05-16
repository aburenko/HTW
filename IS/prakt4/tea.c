/*
  tea.c

  Encryption and Decryption with Tiny Encryption Algorithm (TEA)
  - Block size 64 Bit, Key size 128 Bit
  - encrypt() and decrypt() according to 
    http://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void encrypt (uint32_t* v, uint32_t* k) {
  uint32_t v0=v[0], v1=v[1], sum=0, i; /* set up */
  uint32_t delta=0x9e3779b9; /* a key schedule constant */
  uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3]; /* cache key */

  for (i=0; i < 32; i++) { /* basic cycle start */
    sum += delta;
    v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
    v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);  
  } /* end cycle */
  v[0]=v0; v[1]=v1;
}
 
void decrypt (uint32_t* v, uint32_t* k) {
  uint32_t v0=v[0], v1=v[1], sum=0xC6EF3720, i; /* set up */
  uint32_t delta=0x9e3779b9; /* a key schedule constant */
  uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3]; /* cache key */
  for (i=0; i<32; i++) { /* basic cycle start */
    v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
    sum -= delta;                                   
  } /* end cycle */
  v[0]=v0; v[1]=v1;
}

int main(int argc, char* argv[])
{
  FILE *fin, *fout;
  char key[16];
  char bl[8], blout[8];
  char todo;
  int ret, c;

  if (argc != 5) {
    printf("Usage: %s -e|-d <key> <infile> <outfile>\n", argv[0]);
    exit (EXIT_FAILURE);
  }

  /* determine, what to do */
  if (strcmp(argv[1], "-d") == 0) {
    todo = 'd';
  }
  else {
    if (strcmp(argv[1], "-e") == 0) {
      todo = 'e';
    }
    else {
      printf("Usage: %s -e|-d <key> <infile> <outfile>\n", argv[0]);
      exit (EXIT_FAILURE);
    }
  }

  /* construct the 16-byte-wide key */
  if (strlen(argv[2])==0) {
    printf("No empty passphrase!\n");
    exit(EXIT_FAILURE);
  };
  key[0] = 0;
  for (c=0; c < 16 / strlen(argv[2]); c++) {
    strcat(key, argv[2]);
  }
  strncat(key, argv[2], 16 % strlen(argv[2]));

  printf("Used key = %s, length = %i\n", key, strlen(key));

  fin = fopen(argv[3], "r");
  if (fin == NULL) {
    perror("fopen, infile");
    exit(EXIT_FAILURE);
  }
  fout = fopen(argv[4], "w");
  if (fout == NULL) {
    perror("fopen, outfile");
    exit(EXIT_FAILURE);
  }


  if (todo == 'e') { /* Encryption */
    while(!feof(fin)) {
      ret = fread(&bl, 1, 8, fin);
      /* 
	 Padding 
	 - padding character is 0x00
	 - last byte is number of padding bytes
	 - if plaintext length is multiple of blocklength (8),
           a _full_ block of padding bytes must be appended
      */
      if (ret < 8) {
	for (c=ret; c<7; c++) {
	  bl[c] = 0;
	}
	bl[7] = 8 - ret; /* last byte is number of padding bytes */
      }
      encrypt((uint32_t*) &bl, (uint32_t*) key);
      ret = fwrite(&bl, 1, 8, fout);
      if (ret != 8) {
	perror("fwrite");
	break;
      }
    }
  }

  if (todo == 'd') { /* Decryption */
    ret = fread(&bl, 1, 8, fin);
    if (ret != 8) {
      perror("fread, decryption");
    }
    do {
      decrypt((uint32_t*) &bl, (uint32_t*) key);
      memcpy(blout, bl, 8);
      /* was decrypted block second to last ? */
      ret = fread(&bl, 1, 8, fin);
      if (ret == 0) {
	/* it was; eof reached, 
	   remove padding bytes from last block */
	ret = fwrite(blout, 1, 8-blout[7], fout);
	if (ret != (8-blout[7])) {
	  perror("fwrite, last block");
	  printf("Wrote %i bytes but should write %i\n", ret, 8-blout[7]);
	}
      }
      else {
	fwrite(blout, 1, 8, fout);
	if (ret != 8) {
	  perror("fwrite");
	}
      }
    }
    while (!feof(fin));  
  } /* Decryption */
  
  fclose(fout);
  fclose(fin);
  
  exit(EXIT_SUCCESS);
}
