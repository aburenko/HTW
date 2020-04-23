#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char str[512];
int dis[100];
int countPlaces = 0;
int distance = 7;

int getSubstrPositions(const char * haystack, const char *needle, int i)
{
    const char *tmp = strstr(haystack + i + distance, needle);
    if (tmp == NULL) {
//         printf("ret\n");
        return 0;
    }
    printf("%d - %d\n", tmp, needle);
    dis[countPlaces] = tmp - haystack - i;
    printf("distance %d\n", dis[countPlaces]);
    countPlaces++;
    printf("%d needle %s\n", i, needle);
    printf("cp %d tmp %s\n\n",  countPlaces, tmp );
    return 1;
}

char* substr(const char *src, int m, int n)
{
	// get length of the destination string
	int len = n - m;

	// allocate (len + 1) chars for destination (+1 for extra null character)
	char *dest = (char*)malloc(sizeof(char) * (len + 1));

	// extracts characters between m'th and n'th index from source string
	// and copy them into the destination string
	for (int i = m; i < n && (*(src + i) != '\0'); i++)
	{
		*dest = *(src + i);
		dest++;
	}

	// null-terminate the destination string
	*dest = '\0';

	// return the destination string
	return dest - len;
}

int main(int argc, char* argv[])
{
  FILE *fin;
  int in, c;
  int count = 0;
  
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
    if (isalpha(in) && in != '\n') {
      str[count] = (char)in;
      count++;
    }
  }
  printf("count %d\n", count);
  fclose(fin);
  
  for (c=0; c<100; c++) {
    dis[c] = 0;
  }
  
  int i;
  for(i = 0; i < count - distance - 1; i++) {
      char * substring3 = substr(str, i, i + distance);
      if (getSubstrPositions(str, substring3, i) == 1) {
        i += 4;
      }
  }
  
  printf("matches: \n");
  for (c=0; c<100; c++) {
    if (dis[c] == 0) {
        printf(" found %d\n", c);
        break;
    }
    printf("%d\n", dis[c]);
  }
  
  exit(EXIT_SUCCESS);
}
