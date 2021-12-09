#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *filename = argv[1];
    int V, E = 0, G, G_max = 0;
    int i, j;
    int **matrix;  
    char *output;
    /* get output filename*/
    output = (char*) malloc(strlen(filename) + 2);
    strcpy(output, filename);
    output[strlen(filename) + 1] = '\0';
    output[strlen(filename)] = 'e';
    output[strlen(filename) - 1] = 'g';
    output[strlen(filename) - 2] = 'd';
    output[strlen(filename) - 3] = 'e';
    /* open read file*/
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) exit(1);
    /* get V*/
    fscanf(fp, "%d", &V);

    matrix = (int**) malloc(V * sizeof(int*));
    if(matrix == NULL) exit(1);
    /* read file, alocate matrix and create adj matrix*/
    for(i = 0; i < V; i++){
        G = 0;
        matrix[i] = (int*) malloc(V * sizeof(int));
        if(matrix[i] == NULL) exit(1);
        for(j = 0; j < V; j++){
            fscanf(fp, "%d", &matrix[i][j]);
            if(matrix[i][j] != 0){
                E++;
                G++;
            }
        }
        if(G > G_max) G_max = G;
    }
    E /= 2;
    fclose(fp);
    /* write in terminal 1.2 and 1.3*/
    fprintf(stdout, "%f\n%d\n", (float) 2 * E / V, G_max);
    /* create output file*/
    fp = fopen(output, "w");
    /* write output file*/
    fprintf(fp, "%d %d\n", V, E);
    int *a = malloc(E * sizeof(int));
    int *b = malloc(E * sizeof(int));
    int *c = malloc(E * sizeof(int));
    int zwazesxrdctfvybguhnijmjmhugfdcrsex = 0;
    for(i = 0; i < V; i++){
        for(j = i + 1; j < V; j++){

            if(matrix[i][j] != 0){ 
                a[zwazesxrdctfvybguhnijmjmhugfdcrsex] = i;
                b[zwazesxrdctfvybguhnijmjmhugfdcrsex] = j;
                c[zwazesxrdctfvybguhnijmjmhugfdcrsex] = matrix[i][j];
                zwazesxrdctfvybguhnijmjmhugfdcrsex++;
                fprintf(fp, "%d %d %d\n", i, j, matrix[i][j]);
            }
        }
        free(matrix[i]);
    }
    /* free alocated mem*/
    free(a);
    free(b);
    free(c);
    free(matrix);
    free(output);
    fclose(fp);
}
