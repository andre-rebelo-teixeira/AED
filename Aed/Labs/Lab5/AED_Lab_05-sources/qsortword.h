#ifndef QSORTWORD
#define QSORTWORD

#include "defs.h"

void QuickSort(Item a[], int l, int r, int (*less)(Item, Item));
int partition(Item a[], int l, int r, int (*less)(Item, Item));

#endif