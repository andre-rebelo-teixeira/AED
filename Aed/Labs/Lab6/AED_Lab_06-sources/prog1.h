#ifndef PROG1
#define PROG1

#include <stdio.h>

void correctInvocation();

int **allocateMatrix(int V);

int **fillMatrix(int **mat, FILE *pToFile, int V, int *E, int *G);

void freeMemory1(char *outFileName);

void execice1_4(int **map, int V, int E, FILE *pToFileOut);

#endif