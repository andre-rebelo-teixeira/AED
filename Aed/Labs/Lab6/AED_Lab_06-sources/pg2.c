#include "LinkedList.h"
#include "defs.h"
#include "prog2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
      int V;
      int cost;
} node;

void freeItem(Item node)
{
      free(node);
}

int compare(Item A, Item B)
{
      int i, j;

      i = ((node *)A)->V;
      j = ((node *)B)->V;

      if (i < j)
            return 1;
      else if (i > j)
            return -1;
      else
            return 0;
}

int main(int argc, char **argv)
{
      int V = 0;
      int i = 0;
      int E = 0;
      LinkedList **mat = NULL;
      FILE *pToFileIn = NULL;
      FILE *pToFileOut = NULL;

      char *outFileName = (char *)malloc((strlen(argv[1]) + 2) * sizeof(char));

      strcpy(outFileName, argv[1]);
      strcpy(&outFileName[strlen(argv[1]) - 4], "ladj");

      if (argc != 2)
            correctInvocation();

      pToFileIn = fopen(argv[1], "r");

      pToFileOut = fopen(outFileName, "w");

      fscanf(pToFileIn, "%d", &V);
      fscanf(pToFileIn, "%d", &E);

      mat = startList(V);
      mat = fillList(mat, E, V, pToFileIn);
      printFinal(mat, E, V, pToFileOut);

      for (i = 0; i < V; i++)
            freeLinkedList(mat[i], freeItem);

      free(outFileName);
      fclose(pToFileIn);
      free(mat);

      return 0;
}

LinkedList **fillList(LinkedList **mat, int E, int V, FILE *pToFile)
{
      int i = 0;
      int rows = 0;
      int columns = 0;
      int value = 0;
      int err = 0;

      for (i = 0; i < E; i++)
      {
            node *insert = (node *)malloc(sizeof(node));
            node *insert2 = (node *)malloc(sizeof(node));
            if (insert == NULL || insert2 == NULL)
            {
                  exit(1);
            }
            fscanf(pToFile, "%d %d %d", &rows, &columns, &value);
            insert->cost = value;
            insert->V = rows;
            mat[columns] = insertSortedLinkedList(mat[columns], (Item)insert, compare, &err);
            insert2->V = columns;
            insert2->cost = value;
            mat[rows] = insertSortedLinkedList(mat[rows], (Item)insert2, compare, &err);
      }
      return mat;
}

LinkedList **startList(int V)
{
      int i = 0;
      LinkedList **list = (LinkedList **)calloc(V, sizeof(LinkedList *));
      if (list == NULL)
            for (i = 0; i < V; i++)
                  list[i] = initLinkedList();
      return list;
}

void printFinal(LinkedList **list, int E, int V, FILE *pToFileOut)
{
      int i = 0;
      int j = 0;
      LinkedList *aux = NULL;
      Item aux1;
      int length = 0;

      fprintf(pToFileOut, "%d\n", V);
      for (i = 0; i < V; i++)
      {
            aux = list[i];
            length = lengthLinkedList(list[i]);
            printf("%d\n", length);
            fprintf(pToFileOut, "%d ", i);
            for (j = 0; j < length; aux = getNextNodeLinkedList(aux))
            {
                  aux1 = getItemLinkedList(aux);
                  fprintf(pToFileOut, "%d:%d ", ((node *)aux1)->V, ((node *)aux1)->cost);
                  j += 1;
            }
            fprintf(pToFileOut, "-1\n");
      }
      fclose(pToFileOut);
}

/** 
 * @brief Print a warning related to the number of arguments
 */
void correctInvocation()
{
      printf("The program need at leat 2 arguments\n");
      printf("Try this:\n\t");
      printf("./pg1 <nome do grafo>.adj\n");
}
