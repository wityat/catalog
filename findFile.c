//
// Created by victor on 28.04.2020.
//
#include "CatalogTree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void strrem( char* _pSourceStr, const char* _pDelStr )
{
    char* pTmpStr;

    pTmpStr = strstr( _pSourceStr, _pDelStr );

    strcpy( pTmpStr, pTmpStr + strlen( _pDelStr ) );
};

void find_file(struct Node* root, char* filename, char* path, char** res, int* pointer){
    struct Node* p = root;

    if (strcmp(filename, p->data) == 0){
//        printf("%s %s %d\n", filename, p->data, strcmp(filename, p->data));
        printf("%d\n", *pointer);
        res[&pointer] = path;
        pointer+=1;
        printf("%d\n", *pointer);
    }

    char* del_str = (char *)calloc(sizeof(p->data[0])*strlen(p->data) + 1, sizeof(char));
    strcat(del_str, p->data);
    strcat(del_str, "/");

//    printf("%s\n", del_str);

    strcat(path, del_str);

//    printf("%s\n", path);

    if(p->child)
        find_file(p->child, filename, path, res, pointer);

    strrem(path, del_str);

    if(p->brother)
        find_file(p->brother, filename, path, res, pointer);
    free(del_str);
}
