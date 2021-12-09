/******************************************************************************
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
 ******************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#include "connectivity.h"

#define DEBUG 0

/******************************************************************************
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
 *****************************************************************************/

void quick_find(int *id, int N, FILE * fp, int quietOut)
{
   unsigned long int union_access = 0;
   unsigned long int find_access = 0;  
   int i, p, q, t;
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;
      /* do search first */
      find_access += 2;
      if (id[p] == id[q]) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union */
      for (t = id[p], i = 0; i < N; i++) {
         union_access++;
         if (id[i] == t) {
            id[i] = id[q];
         }
      }
      links_cnt++;
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QF: The number of links performed is %d for %d input pairs. %lu find_access / %lu union_access\n",
          links_cnt, pairs_cnt, find_access, union_access);
   return;
}


/******************************************************************************
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
 *****************************************************************************/

void quick_union(int *id, int N, FILE * fp, int quietOut)
{
   unsigned long int union_access = 0;
   unsigned long int find_access = 0;  
   int i, j, p, q;
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;
      i = p;
      j = q;

      /* do search first */
      find_access++;
      while (i != id[i]) {
         find_access++;
         i = id[i];
      }
      find_access++;
      while (j != id[j]) {
         find_access++;
         j = id[j];
      }
      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union */
      union_access++;
      id[i] = j;
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QU: The number of links performed is %d for %d input pairs. %lu find_access / %lu union_access\n",
          links_cnt, pairs_cnt, find_access, union_access);
}


/******************************************************************************
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
 *****************************************************************************/

void weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{
   unsigned long int union_access = 0;
   unsigned long int find_access = 0;   
   int i, j, p, q;
   int *sz = (int *) malloc(N * sizeof(int));
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;

      /* do search first */
      for (i = p; i != id[i]; i = id[i], find_access++);
      for (j = q; j != id[j]; j = id[j], find_access++);

      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      union_access += 3;
      if (sz[i] < sz[j]) {
         id[i] = j;
         sz[j] += sz[i];
      }
      else {
         id[j] = i;
         sz[i] += sz[j];
      }
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("WQU: The number of links performed is %d for %d input pairs. %lu find_access / %lu union_access\n",
          links_cnt, pairs_cnt, find_access, union_access);
   free(sz);
   return;
}


/******************************************************************************
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
 *****************************************************************************/

void compressed_weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{
   unsigned long int union_access = 0;
   unsigned long int find_access = 0;
   int i, j, p, q, t, x;
   int *sz = (int *) malloc(N * sizeof(int));
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;

      /* do search first */
      for (i = p; i != id[i]; i = id[i], find_access++);
      for (j = q; j != id[j]; j = id[j], find_access++);

      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      union_access += 3;
      if (sz[i] < sz[j]) {
         id[i] = j;
         sz[j] += sz[i];
         t = j;
      }
      else {
         id[j] = i;
         sz[i] += sz[j];
         t = i;
      }
      links_cnt++;

      /* retrace the path and compress to the top */
      for (i = p; i != id[i]; i = x) {
         union_access++;
         x = id[i];
         id[i] = t;
      }
      for (j = q; j != id[j]; j = x) {
         union_access++;
         x = id[j];
         id[j] = t;
      }
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("CWQU: The number of links performed is %d for %d input pairs. %lu find_access / %lu union_access\n",
          links_cnt, pairs_cnt, find_access, union_access);
   free(sz);
   return;
}


typedef struct _connectivity
{
   int index;
   int group;
   struct _connectivity* next;
   
} connectivity;

void count_connections(int *id, int N)
{
   int n_group = 1;
   int exist;
   connectivity* aux;
   connectivity **head = (connectivity**) malloc(sizeof(connectivity*) * N);
   head[0] = (connectivity*) malloc(sizeof(connectivity));
   head[0]->index = 0;
   head[0]->group = id[0];
   head[0]->next = NULL;
   for(unsigned int i = 1; i < N; i++){
      exist = -1;
      for(unsigned int j = 0; j < n_group; j++){
         if(head[j]->group == id[i]){
            exist = j;
            break;
         }
      }
      if(exist == -1){
         head[n_group] = (connectivity*) malloc(sizeof(connectivity));
         head[n_group]->group = id[i];
         head[n_group]->index = i;
         head[n_group]->next = NULL;
         n_group++;
      }
      else{
         aux = (connectivity*) malloc(sizeof(connectivity));
         aux->next = head[exist];
         head[exist] = aux;
         aux->group = id[i];
         aux->index = i;
      }
   }
   
   // ----------------------------------------------------------------------------------

   for(unsigned int i = 0; i < n_group; i++){

      while(head[i] != NULL){
         printf("%d", head[i]->index);
         if(head[i]->next != NULL){
            printf(" - ");
         }
         aux = head[i]->next;
         free(head[i]);
         head[i] = aux;
      }
      printf("\n");
      free(head[i]);
   }
   free(head);
   printf("Numero de conjuntos: %d", n_group);
}

int heighest_tree(int *id, int N)
{
   int maxH = 0, aux = 0;
   int *sz = (int*) calloc(N,sizeof(int));
   for(unsigned int i = 0; i < N; i++){
      aux = recursive(id, i, sz);
      sz[i] = aux;
      if(aux > maxH) maxH = aux;
   }
   return maxH;
}

int recursive(int *id, int i, int *sz)
{
   if(sz[i] != 0)
      return sz[i];
   else if(id[i] == i)
      return 1;
   else
      sz[i] = recursive(id, id[i], sz) + 1;
      return sz[i];
}