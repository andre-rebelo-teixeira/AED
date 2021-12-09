#ifndef PROG2
#define PROG2

#include "defs.h"
#include <stdio.h>

/*typedef struct node node;*/

int compare(Item A, Item B);

void correctInvocation();
void printFinal(LinkedList **list, int E, int V, FILE *pToFileOut);
LinkedList **startList(int V);
LinkedList **fillList(LinkedList **mat, int E, int V, FILE *pToFile);

#endif
