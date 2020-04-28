#include <stdio.h>
#include "CatalogTree.h"
#include "findFile.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
       FILE* fout;
       fout = fopen("1.txt", "w");
       char* path = "/home/victor/test";

       struct Node *root = create(path);

       root = make(path, root);
       print(root, 0, fout);
       fclose(fout);

       char ** res = (char **)calloc(100, sizeof(char*));
       for (int i = 0; i < 100; ++i)
           res[i] = (char *)calloc(1000, sizeof(char));

       path = (char *)calloc(1000, sizeof(char));
//       path = root->data;
       int pointer = 0;
       find_file(root, "1.txt", path, res, &pointer);
       for (int i = 0; i < pointer; ++i)
           printf("%s\n", res[i]);


       return 0;
}
