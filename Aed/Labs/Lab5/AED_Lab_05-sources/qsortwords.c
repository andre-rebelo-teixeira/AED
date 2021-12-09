#include "defs.h"
#include "word.h"
#include "qsortword.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define exch(A, B)      \
      {                 \
            Item t = A; \
            A = B;      \
            B = t;      \
      }

#define key(A) (A)

#define eq(A, B) (!less(A, B) && !less(B, A))

int OP_CNT;

enum sort_order
{
      ascending,
      descending
};

enum sort_criteria
{
      alphabetic,
      length,
      occurrences
};

/******************************************************************************
* main ()
*
*****************************************************************************/

int main(int argc, char **argv)
{
      int TnumWords;   /* total number of words in input file */
      int numWords;    /* number of distint words in input file */
      Tabword tabword; /* table holding the structure */

      /* default initialization for alfabetic order and ascending */
      enum sort_criteria criterio = alphabetic;
      enum sort_order sentido = ascending;
      char *file = argv[1];

      argv++; /* get past prog and file names */
      while (*(++argv))
      {
            if (strcmp(*argv, "-alfabetica") == 0)
                  criterio = alphabetic;
            else if (strcmp(*argv, "-ocorrencias") == 0)
                  criterio = occurrences;
            else if (strcmp(*argv, "-comprimento") == 0)
                  criterio = length;
            else if (strcmp(*argv, "-a") == 0)
                  sentido = ascending;
            else if (strcmp(*argv, "-d") == 0)
                  sentido = descending;
            else
            {
                  fprintf(stderr, "Wrong arguments\n");
                  exit(3);
            }
      }
      TnumWords = AllocWordArray(&tabword, file);
      printf("Total number of words: %d\n", TnumWords);

      numWords = FillInWordArray(tabword, file);
      printf("Number of different words = %d\n", numWords);

      OP_CNT = 0; /* Certified it is a zer */

      /*  Call the sorting function using as argument the
       appropriate comparison function selected by user option */

      if ((criterio == alphabetic) && (sentido == ascending))
      {
            QuickSort((void **)tabword, 0, numWords - 1, LessAlphabetic);
      }
      else if ((criterio == alphabetic) && (sentido == descending))
      {
            QuickSort((void **)tabword, 0, numWords - 1, MoreAlphabetic);
      }
      else if ((criterio == occurrences) && (sentido == ascending))
      {
            QuickSort((void **)tabword, 0, numWords - 1, LessWords);
      }
      else if ((criterio == occurrences) && (sentido == descending))
      {
            QuickSort((void **)tabword, 0, numWords - 1, Morewords);
      }
      else if ((criterio == length) && (sentido == ascending))
      {
            QuickSort((void **)tabword, 0, numWords - 1, LessSize);
      }
      else if ((criterio == length) && (sentido == descending))
      {
            QuickSort((void **)tabword, 0, numWords - 1, MoreSize);
      }

      /* ---------------------------------------- */
      printf("Accesses count for sort: %d\n", OP_CNT);

      WriteFile(tabword, file, numWords);
      /*  printf("Number of different words: %d\n", n_palavras);  */

      /* -- Insert code to call functions to free allocated memory -- */
      tabword = FreeWordArray(&tabword, TnumWords);
      /*==== TODO ====*/

      /* ------------------------------------------------------------ */

      return 0;
}

void QuickSort(Item a[], int l, int r, int (*less)(Item, Item))
{

      int i, j, k, p, q;
      Item v;

      if (r <= l)
            return;

      v = a[r];
      i = l - 1;
      j = r;
      p = l - 1;
      q = r;
      for (;;)
      {
            while (less(a[++i], v))
                  OP_CNT++;
            while (less(v, a[--j]))
            {
                  OP_CNT++;
                  if (j == l)
                        break;
            }
            if (i >= j)
                  break;
            exch(a[i], a[j]);
            OP_CNT += 2;
            if (eq(a[i], v))
            {
                  OP_CNT++;
                  p++;
                  exch(a[p], a[i]);
            }
            OP_CNT++;
            if (eq(v, a[j]))
            {
                  OP_CNT++;
                  q--;
                  exch(a[q], a[j]);
            }
      }
      exch(a[i], a[r]);
      OP_CNT++;
      j = i - 1;
      i = i + 1;
      for (k = l; k <= p; k++, j--)
      {
            OP_CNT++;
            exch(a[k], a[j]);
      }
      for (k = r - 1; k >= q; k--, i++)
      {
            OP_CNT++;
            exch(a[k], a[i]);
      }
      QuickSort(a, l, j, less);
      QuickSort(a, i, r, less);
}

int partition(Item a[], int l, int r, int (*less)(Item, Item))
{
      int i, j;
      Item v;

      v = a[r];
      i = l - 1;
      j = r;

      for (;;)
      {
            OP_CNT += 1;
            while (less(a[++i], v))
                  OP_CNT += 2;
            while (less(v, a[--j]))
            {
                  OP_CNT += 2;
                  if (j == l)
                        break;
            }
            if (i >= j)
                  break;
            exch(a[i], a[j]);
      }
      exch(a[i], a[r]);
      OP_CNT += 1;
      return i;
}
