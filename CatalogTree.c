#include "CatalogTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

struct Node* create(void* _data, int type, long int size)
{
    struct Node* root = (struct Node*) malloc(sizeof(struct Node));
    root->data = (char*)_data;
    root->type = type;
    root->size = size;
    root->brother = NULL;
    root->child = NULL;
    return root;
}

struct Node* add_brother(struct Node* old_brother, void* _data, int type, long int size)
{
    struct Node* p = old_brother;
    while(p && p->brother)
        p = p->brother;

    if(p)
        p->brother = create(_data, type, size);
    else
        create(_data, type, size);
    return old_brother;
}

struct Node* add_child(struct Node *p, void* _data, int type, long int size)
{
    if(p && p->child)
        p->child = add_brother(p->child, _data, type, size);
    else if (p)
        p->child = create(_data, type, size);
    return p;
}

void print(struct Node* root, int offset){
    struct Node* p = root;
    for(int i=0; i < offset; ++i)
        printf(" ");
    printf("%s\n", p->data);
    if(p->child)
        print(p->child, offset + (int) strlen(p->data));
    if(p->brother)
        print(p->brother, offset);
}

struct Node* delete(struct Node* root) {
    struct Node *p = root;
    if (p->brother)
        p->brother = delete(p->brother);
    if (p->child)
        p->child = delete(p->child);
    free(p);
    return 0;
}

char* make_str(char* str, int plus){
    char* tmp = (char*) malloc(strlen(str)+1+plus);
    strcpy(tmp, str);
    return tmp;
}

off_t fsize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    return 0;
}

struct Node* make(char* path, struct Node* root) {
    struct dirent *de;

    DIR *dr = opendir(path);

    if (dr == NULL)
    {
        return root;
    }

    while ((de = readdir(dr)) != NULL){
        char* tmp = make_str(de->d_name, 0);
        char* path1 = (char *)calloc(1000, sizeof(char));
        strcpy(path1, path);
        strcat(path1, "/");
        strcat(path1, de->d_name);
        if(de->d_type == DT_DIR && !(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)){
            root = add_child(root, (void*) tmp, DIR_, fsize(de->d_name));
            struct Node* p = root->child;
            while(p && p->brother)
                p = p->brother;
            make(path1, p);
        }else if (de->d_type == DT_REG && !(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)){
//            printf("name: %s\n", de->d_name);
            root = add_child(root, (void*) tmp, FILE_, fsize(path1));
        }
        free(path1);
    }
    closedir(dr);
//
    return root;
}