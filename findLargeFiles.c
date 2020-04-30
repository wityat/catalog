#include "CatalogTree.h"
#include "strrem.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void find_large_file(struct Node* root,long int size, char* path)
{
    struct Node* p = root;

    char* del_str = make_str(p->data, strlen("/"));
    strcat(del_str, "/");

    strcat(path, del_str);

    if(p->size > size && p->type == FILE_)
        printf("%s: %ld\n", path, p->size);
    if (p->child)
        find_large_file(p->child, size, path);

    strrem(path, del_str);
    free(del_str);

    if (p->brother)
        find_large_file(p->brother, size, path);
}
