#ifndef _DIRECTORY_TREE_H
#define _DIRECTORY_TREE_H

#include <stdio.h>

typedef struct _directoryTree {
    FILE *fptr;
    char *root; 
} directoryTree;

directoryTree* allocate_directoryTree(char *root);
void freeDirectoryTree(directoryTree* directoryTreePtr);
void SerachDirectoryTree(directoryTree* directoryTreePtr);

#endif