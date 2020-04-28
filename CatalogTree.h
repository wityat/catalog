#ifndef CATALOG_CATALOGTREE_H
#define CATALOG_CATALOGTREE_H

#include <bits/types/FILE.h>

struct Node{
    char* data;
    struct Node* child;
    struct Node* brother;
} ;
struct Node* make(char* path, struct Node* root);
void print(struct Node* root, int lvl, FILE *fout);
struct Node* create(void *_data);
#endif //CATALOG_CATALOGTREE_H
