#include "CatalogTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

struct Node* create(void* _data)
{
    struct Node* root = (struct Node*) malloc(sizeof(struct Node));
    root->data = (char*)_data;
    root->brother = NULL;
    root->child = NULL;
    return root;
}

struct Node* add_brother(struct Node* old_brother, void* _data)
{
    struct Node* p = old_brother;
    while(p && p->brother)
        p = p->brother;

    if(p)
        p->brother = create(_data);
    else
        p = create(_data);
    return old_brother;
}

struct Node* add_child(struct Node *p, void* _data)
{
    if(p && p->child)
        p->child = add_brother(p->child, _data);
    else if (p)
        p->child = create(_data);
    return p;
}

void print(struct Node* root, int lvl, FILE *fout){
    struct Node* p = root;
    for(int i=0; i < lvl; ++i)
        fprintf(fout, "    ");
    fprintf(fout, "%s\n", p->data);
    if(p->child)
        print(p->child, lvl+1, fout);
    if(p->brother)
        print(p->brother, lvl, fout);
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

char* make_str(char* str){
    char* tmp = (char*) malloc(strlen(str)+1);
    strcpy(tmp, str);
    return tmp;
}

struct Node* make(char* path, struct Node* root) {
    struct dirent *de;

    DIR *dr = opendir(path);

    if (dr == NULL)
    {
        return root;
    }

    while ((de = readdir(dr)) != NULL){
        char* tmp = make_str(de->d_name);
        if(de->d_type == DT_DIR && !(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)){
            printf("name: %s\n", de->d_name);
            root = add_child(root, (void*) tmp);
            char* path1 = (char *)calloc(1000, sizeof(char));
            strcpy(path1, path);
            strcat(path1, "/");
            strcat(path1, de->d_name);
            struct Node* p = root->child;
            while(p && p->brother)
                p = p->brother;
            p = make(path1, p);
            free(path1);
        }else if (de->d_type == DT_REG && !(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)){
            printf("name: %s\n", de->d_name);
            root = add_child(root, (void*) tmp);
        }
    }
    closedir(dr);
//
    return root;
}