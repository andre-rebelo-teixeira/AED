/**************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-02-22
 *
 * NAME
 *   connectivity.c
 *
 * DESCRIPTION
 *   Algorithms for solving the connectivity problem -  QF QU WQU CWQU
 *   For each method count number of entry pairs and the number of links
 *
 * COMMENTS
 *   Code for public distribution
 **************************/
#include <stdio.h>
#include <stdlib.h>

#include "connectivity.h"

#define DEBUG 0

/**************************
 * quick_find()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Find algorithm
 ***************************/

void quick_find(int *id, int N, FILE *fp, int quietOut)
{
   int i, p, q, t;
   int pairs_cnt = 0; /* connection pairs counter */
   int links_cnt = 0; /* number of links counter */
   unsigned long int total = 0;
   unsigned long int find = 0;
   unsigned long int Union = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++)
   {
      id[i] = i;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2)
   {
      pairs_cnt++;
      find += 2;
      if (id[p] == id[q])
      {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union */
      Union++; //* t = id[p]
      for (t = id[p], i = 0; i < N; i++)
      {
         Union++; //*n id[i] == t
         if (id[i] == t)
         {
            Union += 2; //* id[i] = id[q]
            id[i] = id[q];
         }
      }
      links_cnt++;
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QF: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   total = find + Union;
   printf("\n\ntotal = %lu; find = %lu; Union = %lu \n\n", total, find, Union);
   return;
}

/**************************
 * quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Union algorithm
 ***************************/

void quick_union(int *id, int N, FILE *fp, int quietOut)
{

   int i, j, p, q;
   int pairs_cnt = 0; /* connection pairs counter */
   int links_cnt = 0; /* number of links counter */
   unsigned long int total = 0;
   unsigned long int find = 0;
   unsigned long int Union = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++)
   {
      id[i] = i;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2)
   {
      pairs_cnt++;
      i = p;
      j = q;

      /* do search first */
      find++; //* 1st time i != id[i]
      while (i != id[i])
      {
         i = id[i];
         find += 2; //* time i != id[i] & i = id[i];
      }
      find++; //* 1st time j != id[j]
      while (j != id[j])
      {
         j = id[j];
         find += 2; //* time j != id[j] & i = id[j];
      }
      if (i == j)
      {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union */
      Union++;
      id[i] = j;
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   total = find + Union;
   printf("\n\ntotal = %lu; find = %lu; Union = %lu \n\n", total, find, Union);
}

/**************************
 * weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Weighted Quick Union algorithm
 ***************************/

void weighted_quick_union(int *id, int N, FILE *fp, int quietOut)
{

   int i, j, p, q;
   int *sz = (int *)malloc(N * sizeof(int));
   int pairs_cnt = 0; /* connection pairs counter */
   int links_cnt = 0; /* number of links counter */
   unsigned long int total = 0;
   unsigned long int find = 0;
   unsigned long int Union = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++)
   {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2)
   {
      pairs_cnt++;

      /* do search first */
      find++; //* first for loop check
      for (i = p; i != id[i]; i = id[i])
         find += 2; //* i != id[i] & i = id[i]
      ;
      find++; //* first for loop check
      for (j = q; j != id[j]; j = id[j])
         find += 2; //* j != id[j] & j = id[j]
      ;

      if (i == j)
      {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      Union += 2; //* sz[i] < sz[j]
      if (sz[i] < sz[j])
      {
         id[i] = j;
         sz[j] += sz[i];
         Union += 3; //* id[i] = j; & sz[j] += sz[i];
      }
      else
      {
         id[j] = i;
         sz[i] += sz[j];
         Union += 3; //* id[j] = i; & sz[i] += sz[j];
      }
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("WQU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   total = find + Union;
   printf("\n\ntotal = %lu; find = %lu; Union = %lu \n\n", total, find, Union);
}

/**************************
 * compressed_weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Compressed Weighted Quick Union algorithm
 ***************************/

void compressed_weighted_quick_union(int *id, int N, FILE *fp, int quietOut)
{
   int i, j, p, q, t, x;
   int *sz = (int *)malloc(N * sizeof(int));
   int pairs_cnt = 0; /* connection pairs counter */
   int links_cnt = 0; /* number of links counter */
   unsigned long int total = 0;
   unsigned long int find = 0;
   unsigned long int Union = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++)
   {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2)
   {
      pairs_cnt++;

      /* do search first */
      find++; //* first loop iteration
      for (i = p; i != id[i]; i = id[i])
         find += 2;
      ;
      find++; //* first loop iteration
      for (j = q; j != id[j]; j = id[j])
         find += 2;
      ;

      if (i == j)
      {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      Union += 2; //* sz[i] < sz[j
      if (sz[i] < sz[j])
      {
         id[i] = j;
         sz[j] += sz[i];
         t = j;
         Union += 3;
      }
      else
      {
         id[j] = i;
         sz[i] += sz[j];
         t = i;
         Union += 3;
      }
      links_cnt++;

      /* retrace the path and compress to the top */
      Union++;
      for (i = p; i != id[i]; i = x)
      {
         x = id[i];
         id[i] = t;
         Union += 3;
      }
      Union++;
      for (j = q; j != id[j]; j = x)
      {
         x = id[j];
         id[j] = t;
         Union += 3;
      }
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("CWQU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   total = find + Union;
   printf("\n\ntotal = %lu; find = %lu; Union = %lu \n\n", total, find, Union);
   return;
}