#include<stdio.h>

int sort(char * array, int n) { //array and size
    int i,u;
    for(i=0; i<n-1; i++)
    {
      for(u=i+1; u<n; u++)
      {
        if(array[i] > array[u])
          swap(array,i,u);
      }
    }
}

int swap(char * array, int i, int u) {
    char temp=array[i];
    array[i]=array[u];
    array[u]=temp;
}
