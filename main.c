#include <stdio.h>
#include "CatalogTree.h"
#include "findFile.h"
#include "quantity.h"
#include "findLargeFile.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char* path = "/home/victor/test";
    char* filename = "1.txt";

    struct Node *root = create(path, 0, 0);
    root = make(path, root);

    printf("\n\nBeautiful print of catalog:\n");
    print(root, 0);

    char **res = (char**) calloc(1, sizeof(char*));
    path = (char *)calloc(1000, sizeof(char));
    int pointer = 0;

    find_file(root, filename, path, res, &pointer);

    if (pointer > 0) {
        printf("\nFolders with current file:\n");
        for (int i = 0; i < pointer; ++i)
            printf("%s\n", res[i]);
    }
    else
        printf("\nThere is no folders with current file!\n");

    printf("\nAmount of files in every folder:\n");
    get_quantity(root, 0, path);

    long int fsize = 2;
    fsize *= 1024;
    printf("\nFiles larger than the specified size:\n");
    find_large_file(root, fsize, path);

    free(res);
    for (int i = 0; i < pointer; ++i)
        free(res[i]);


    return 0;
}
