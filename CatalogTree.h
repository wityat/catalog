#ifndef CATALOG_CATALOGTREE_H
#define CATALOG_CATALOGTREE_H

#include <bits/types/FILE.h>
enum type {NONE, DIR_, FILE_};
struct Node{
    char* data;
    int type;
    long int size;
    struct Node* child;
    struct Node* brother;
} ;
struct Node* make(char* path, struct Node* root);
void print(struct Node* root, int offset);
struct Node* create(void* _data, int type, long int size);
char* make_str(char* str, int plus);
#endif //CATALOG_CATALOGTREE_H
