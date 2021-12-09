#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "LinkedList.h"

#define check_pointer(A) if(A == NULL) exit(1)
#define read(A) fscanf(fp, "%d", &A);

typedef struct {int V; int Cost;} pg2;

void freeItem(Item this){
    free((pg2*) this);
}

int  compareItems(Item it1, Item it2)
{
    int i1, i2;

    i1 = ((pg2*)it1)->V;
    i2 = ((pg2*)it2)->V;

    if (i1 < i2)
        return -1;
    if (i1 > i2)
        return 1;
    return 0;
}

int main(int argc, char **argv)
{
    char *filename = argv[1];
    int V, E;
    int p, err;
    int i, j, cost;
    FILE *fp;
    LinkedList **array;
    LinkedList *aux;
    int length;
    pg2 *it1, *it2;
    /* open file*/
    fp = fopen(filename, "r");
    check_pointer(fp);
    /* get vertices and edges*/
    read(V);
    read(E);
    /* allocate and init array for lists*/
    array = (LinkedList**) malloc(V * sizeof(LinkedList*));
    for(i = 0; i < V; i++){
        array[i] = initLinkedList();
    }
    /* create lists*/
    for(p = 0; p < E; p++){
        it1 = (pg2*) malloc(sizeof(pg2));
        it2 = (pg2*) malloc(sizeof(pg2));
        fscanf(fp, "%d %d %d", &i, &j, &cost);
        it1->V = i;
        it1->Cost = cost;
        array[j] = insertSortedLinkedList(array[j], (Item) it1, compareItems, &err);
        it2->V = j;
        it2->Cost = cost;
        array[i] = insertSortedLinkedList(array[i], (Item) it2, compareItems, &err);
    }
    fclose(fp);
    /* change filename*/
    strcpy(&(filename[strlen(filename) - 4]), "ladj");
    /* write output file*/
    fp = fopen(filename, "w");
    
    fprintf(fp, "%d\n", V);

    for(i = 0; i < V; i++){
        aux = array[i];
        length = lengthLinkedList(array[i]);
        for(j = 0; j < length; j++, aux = getNextNodeLinkedList(aux)){
            it1 = getItemLinkedList(aux);
            fprintf(fp, "%d:%d ", it1->V, it1->Cost);
        }
        fprintf(fp,"-1\n");
    }
    fclose(fp);
    /* free array of lists*/
    for (i = 0; i < V; i++){
        freeLinkedList(array[i], freeItem);
    }
    free(array);
    

}