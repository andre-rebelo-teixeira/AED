#include "prog1.h"
#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
      int V = 0;
      int G = 0;
      int E = 0;
      int **mat = NULL;
      FILE *pToFileIn = NULL;
      FILE *pToFileOut = NULL;
      char *outFileName = (char *)malloc((strlen(argv[1]) + 2) * sizeof(char));

      strcpy(outFileName, argv[1]);
      strcpy(&outFileName[strlen(argv[1]) - 4], ".edge");

      if (argc != 2)
            correctInvocation();

      pToFileIn = fopen(argv[1], "r");

      if (pToFileIn == NULL)
            freeMemory1(outFileName);

      pToFileOut = fopen(outFileName, "w");

      fscanf(pToFileIn, "%d", &V);

      mat = allocateMatrix(V);
      if (mat == NULL)
      {
            freeMemory1(outFileName);
      }

      mat = fillMatrix(mat, pToFileIn, V, &E, &G);

      /*1.2 Answer */
      printf("1.2. The graph density is: %f\n", (float)2 * E / V);
      /*1.3 Answer */
      printf("1.3. Biggest graph level is %d\n", G);
      execice1_4(mat, V, E, pToFileOut);

      free(outFileName);
      fclose(pToFileOut);
      fclose(pToFileIn);

      return 0;
}

/**
 * @brief frees memorie of allocaded string for the output file
 * @param outFileName pointer to the string containing the output file name
 */
void freeMemory1(char *outFileName)
{
      free(outFileName);
      exit(1);
}

/**
 * @brief Code that makes what is asked for the 1.3 exercice
 * @param map 2D array containing the adjacent matrix
 * @param V Number of vertices in the array
 * @param E number of Edges in the array 
 * @param pToFileOut pointer to the output file 
 * 
 * @Side effects -> frees the array 
 */
void execice1_4(int **map, int V, int E, FILE *pToFileOut)
{
      int i = 0;
      int j = 0;

      fprintf(pToFileOut, "%d\n%d\n", V, E);

      for (i = 0; i < V; i++)
      {
            for (j = i + 1; j < V; j++)
            {
                  if (map[i][j] != 0)
                        fprintf(pToFileOut, "%d %d %d\n", i, j, map[i][j]);
            }
            free(map[i]);
      }
      free(map);
}

/** 
 * @brief Fills the array with the correct values
 * @param mat Pointer to the 2D array 
 * @param pToFileIn Pointer to the file containng the data
 * @param V number of sides of array 
 * @return Pointer to the new map fully done
 */
int **fillMatrix(int **mat, FILE *pToFile, int V, int *E, int *G)
{
      int columns = 0;
      int rows = 0;
      int internG = 0;

      while (rows != V)
      {
            internG = 0;
            for (columns = 0; columns < V; columns++)
            {
                  fscanf(pToFile, "%d", &mat[rows][columns]);
                  if (mat[rows][columns] != 0)
                  {
                        *E += 1;
                        internG += 1;
                  }
            }

            if (internG > *G)
                  *G = internG;
            rows += 1;
      }
      *E /= 2;
      return mat;
}

/**
 * @brief Allocates the matrix containing information
 * @param V number of vertices the graph has
 * @return Pointer to the 2D array
 */
int **allocateMatrix(int V)
{
      int i;
      int **mat = (int **)malloc(V * sizeof(int *));

      if (mat == NULL)
            return NULL;

      for (i = 0; i < V; i++)
      {
            mat[i] = (int *)malloc(V * sizeof(int));
            if (mat[i] == NULL)
                  return NULL;
      }

      return mat;
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
