#include <stdio.h>
#include <stdlib.h>

int id[] = {0, 1, 9, 4, 9, 6, 9, 7, 0, 9};

int isConnected(int i, int j)
{
      while (i != id[i])
            i = id[i];
      while (j != id[j])
            j = id[j];

      return (i == j);
}

int main()
{
      printf("%d-%d", isConnected(3, 4), isConnected(2, 7));
}