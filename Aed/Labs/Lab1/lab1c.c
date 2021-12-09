#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 25

int main(int argc, char **argv)
{
    char **table;

    long long int x = 10000000;

    while (x)
    {
        table = (char **)malloc(sizeof(char *) * 5);

        for (int i = 0; i < 5; i++)
        {
            table[i] = (char *)malloc(sizeof(char) * STRING_SIZE);
        }

        for (int i = 0; i < 5; i++)
            free(table[i]);

        free(table);

        x--;
    }

    return 0;
}