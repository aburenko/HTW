#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define N 1000

#define DATFILE "hashes.dat"
#define FILE1 "file1.in"
#define FILE2 "file2.in"

#define CMD1 "md5sum < "FILE1" | cut -f1 -d ' '> "DATFILE
#define CMD2 "md5sum < "FILE2" | cut -f1 -d ' '>> "DATFILE

unsigned long countChangedBits(unsigned long long xor) {
    unsigned long count = 0; 
    while (xor) { 
        count += xor & 1; 
        xor >>= 1; 
    } 
    return count; 
}

int main(void)
{
  FILE *f1, *f2, *f3;
  unsigned long long llhi1, lllo1, llhi2, lllo2, xor1, xor2;
  int bits_changed, sum_bits_changed, iterations;
  char buf[17];
  double chbits_per_iteration = 0.0;

  /* statistics init */
  sum_bits_changed = 0;

  /* generate test files which differ in exactly one bit */
  if ((f1 = fopen(FILE1, "w")) == NULL) {
    perror("fopen, f1");
    exit(EXIT_FAILURE);
  }
  if ((f2 = fopen(FILE2, "w")) == NULL) {
    perror("fopen, f2");
    exit(EXIT_FAILURE);
  }
  fputc('b', f1);
  fputc('c', f2);
  fclose(f1);
  fclose(f2);

  /*
    Master Loop
  */

  for (iterations=0; iterations<N; iterations++) {

    /* call md5sum (write result into DATFILE) */
    system(CMD1);
    system(CMD2);

    /* analyze DATFILE */
    
    if ((f3 = fopen(DATFILE, "r")) == NULL) {
      perror("fopen, datfile");
      exit(EXIT_FAILURE);
    }
    
    /* Hash of file1 */
    buf[16] = 0;
    fread(buf, 16, 1, f3);
    llhi1 = strtoull(buf, NULL, 16);
    fread(buf, 16, 1, f3);
    lllo1 = strtoull(buf, NULL, 16);
    printf("Hash of file1: %016llx:%016llx\n", llhi1, lllo1);
    
    getc(f3);   
    /* read \n from DATFILE */
    /* Hash of file2 */
    fread(buf, 16, 1, f3);
    llhi2 = strtoull(buf, NULL, 16);
    fread(buf, 16, 1, f3);
    lllo2 = strtoull(buf, NULL, 16);
    printf("Hash of file2: %016llx:%016llx\n", llhi2, lllo2);
    
    fclose(f3);

    xor1 = llhi1 ^ llhi2;
    xor2 = lllo1 ^ lllo2;
  
    bits_changed = 0;
    bits_changed += countChangedBits(xor1);
    bits_changed += countChangedBits(xor2);
    printf("Bits changed: %d\n", bits_changed);

    /* update statistics */
    sum_bits_changed += bits_changed;

    /* generate two new files which differ in exactly one bit 
       by appending the same char to both files */
    if ((f1 = fopen(FILE1, "a")) == NULL) {
      perror("fopen, f1");
      exit(EXIT_FAILURE);
    }
    if ((f2 = fopen(FILE2, "a")) == NULL) {
      perror("fopen, f2");
      exit(EXIT_FAILURE);
    }
    fputc('a', f1);
    fputc('a', f2);
    fclose(f1);
    fclose(f2);

  } /* Master Loop */

  /* Results */
  chbits_per_iteration = sum_bits_changed / N;
  printf("On average, %.2f bits have changed for %i test cases.", 
	 chbits_per_iteration, N);
  printf(" That are %.2f%%.\n", chbits_per_iteration/1.28);

  /* clean up */
  unlink(DATFILE);
  unlink(FILE1);
  unlink(FILE2);

  return(EXIT_SUCCESS);
}
