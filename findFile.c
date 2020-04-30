#include "CatalogTree.h"
#include <string.h>
#include <stdlib.h>
#include "strrem.h"

void find_file(struct Node* root, char* filename, char* path, char **res, int *pointer){
    struct Node* p = root;

    if (strcmp(filename, p->data) == 0){
        res = (char**)realloc(res, (*pointer+1)*sizeof(char*));
        res[*pointer] = (char *)calloc(strlen(path), sizeof(char));
        strcpy(res[*pointer], path);
        *pointer = *pointer + 1;
    }

    char* del_str = make_str(p->data, strlen("/"));
    strcat(del_str, "/");

    strcat(path, del_str);

    if(p->child)
        find_file(p->child, filename, path, res, pointer);

    strrem(path, del_str);
    free(del_str);

    if(p->brother)
        find_file(p->brother, filename, path, res, pointer);
}
