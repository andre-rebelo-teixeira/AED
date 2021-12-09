/******************************************************************************
 * (c) 2010-2020 IST AED Team
 * Last modified: abl 2020-04-21
 *
 * NAME
 *   sortwords.c
 *
 * DESCRIPTION
 *   Main program for unique word finding and sorting with tables
 *
 * COMMENTS
 *   Code for preliminary distribution, to be completed
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "defs.h"
#include "word.h"

#define exch(t, x, y) t = x; x = y; y = t;

enum sort_order {ascending, descending};

enum sort_criteria {alphabetic, length, occurrences};


int OP_CNT = 0;     /* global variable, to simplify complexity assessment */


/******************************************************************************
 * sort ()
 *
 * Arguments: a - table of items to sort
 *            l, r - limits on table to consider
 *            less - item comparison function
 * Returns: (void)
 * Side-Effects: table is sorted in place
 *
 * Description: implements "some" sorting algorithm for abstract type (Item),
 *       using also an abstract type comparison function (*less)
 *           a[] - array of abstract type Item to be sorted
 *           l - index of first element in the array to be sorted
 *           r - last element of the array to be sorted
 *           (*less)(Item,Item) - abstract type comparison function
 *****************************************************************************/

int partition(Item a[], int l, int r, int (*less) (Item, Item))
{
    int i, j;
    Item v, t;
    
    int m = (r - l) / 2;
    OP_CNT++;
    if(less(a[l], a[m])){
        exch(t, a[l], a[m]);
        OP_CNT++;
    }
    OP_CNT++;
    if(less(a[m], a[r])){
        exch(t, a[m], a[r]);
        OP_CNT++;
    }
    OP_CNT++;
    if(less(a[l], a[m])){
        exch(t, a[l], a[m]);
        OP_CNT++;
    }
    OP_CNT++;
    exch(t, a[m], a[r]);
    
    v = a[r];
    i = l - 1;
    j = r;

    for(;;){
        OP_CNT++;
        while(less(a[++i], v))
            OP_CNT++;
        OP_CNT++;
        while(less(v, a[--j])){
            OP_CNT++;
            if(j == l) break;
        }
        if(i >= j) break;
        OP_CNT++;
        exch(t, a[i], a[j]);
    }
    OP_CNT++;
    exch(t, a[i], a[r]);
    return i;
}

void sort(Item a[], int l, int r, int (*less) (Item, Item))
{
    int i;
    if(r <= l) return;
    i = partition(a, l, r, less);
    sort(a, l, i - 1, less);
    sort(a, i + 1, r, less);
}


/******************************************************************************
* main ()
*
*****************************************************************************/

int main(int argc, char **argv)
{
    int TnumWords;              /* total number of words in input file */
    int numWords;               /* number of distint words in input file */
    Tabword tabword;              /* table holding the structure */

    /* default initialization for alfabetic order and ascending */
    enum sort_criteria criterio = alphabetic;
    enum sort_order sentido  = ascending;
    char *file = argv[1];

    argv++;             /* get past prog and file names */
    while (*(++argv)) {
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
        else {
            fprintf(stderr, "Wrong arguments\n");
            exit(3);
        }
    }
    TnumWords = AllocWordArray(&tabword, file);
    printf("Total number of words: %d\n", TnumWords);

    numWords = FillInWordArray(tabword, file);
    printf("Number of different words = %d\n", numWords);

    OP_CNT = 0;

    /*  Call the sorting function using as argument the
        appropriate comparison function selected by user option */

    if ((criterio == alphabetic) && (sentido == ascending)) {

        /*==== TODO ====*/
        /* -- sort(....); -- */
        sort((void**)tabword, 0, numWords - 1, LessAlphabetic);
        
    }
    if ((criterio == alphabetic) && (sentido == descending)) {

        /*==== TODO ====*/
        /* -- sort(....); -- */
        sort((void**)tabword, 0, numWords - 1, MoreAlphabetic);
    }
    if ((criterio == occurrences) && (sentido == ascending)) {

            /*==== TODO ====*/
            /* -- sort(....); -- */
            sort((void**)tabword, 0, numWords - 1, LessNumUses);
    }
    if ((criterio == occurrences) && (sentido == descending)) {

        /*==== TODO ====*/
        /* -- sort(....); -- */
        sort((void**)tabword, 0, numWords - 1, MoreNumUses);
    }
    if ((criterio == length) && (sentido == ascending)) {

        /*==== TODO ====*/
        /* -- sort(....); -- */
        sort((void**)tabword, 0, numWords - 1, LessLength);
    }
    if ((criterio == length) && (sentido == descending)) {

        /*==== TODO ====*/
        /* -- sort(....); -- */
        sort((void**)tabword, 0, numWords - 1, MoreLength);
    }
    /* other user options */
    /*==== TODO ====*/

    /* ---------------------------------------- */
    printf("Accesses count for sort: %d\n", OP_CNT);

    WriteFile(tabword, file, numWords);
    /*  printf("Number of different words: %d\n", n_palavras);  */

    /* -- Insert code to call functions to free allocated memory -- */
    FreeWordArray(&tabword, numWords);

    /*==== TODO ====*/

    /* ------------------------------------------------------------ */

    return 0;
}
