#include <stdio.h>

void outPost (char * a) {
  printf("Funktion outPost: %s", a);
}

int main(void) {
  char posted[256];
  fgets(posted,256,stdin);  
  printf("Content-Type: text/html;charset=us-ascii\n\n");
  printf("Hello world<br>\n\n");
  printf("<form action='' method='POST'><br>");
  printf("<input type='text' name='firstname' value='Mickey'><br>");
  printf("<input type='text' name='last' value='Mouse'><br>");
  printf("<input type='submit' value='Submit'></form>");
  outPost(posted);
  return 0;
}
