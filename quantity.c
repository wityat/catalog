#include "CatalogTree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "strrem.h"


int get_quantity(struct Node* root, int count, char* path)
{
    struct Node* p = root;

    char* del_str = make_str(p->data, strlen("/"));
    strcat(del_str, "/");

    strcat(path, del_str);

    if (p->child){
        count = get_quantity(p->child, 0, path);
        printf("%s: %d\n", path,count);
    }

    strrem(path, del_str);
    free(del_str);

    if (p->brother)
        count += get_quantity(p->brother, 0, path);
    if (p->type == FILE_) count += 1;
    return count;
}