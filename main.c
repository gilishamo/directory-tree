#include <stdio.h>
#include "directory_tree.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("ERROR: provide a path to a directory");
        return 1;
    }

    directoryTree *d;

    d = allocate_directoryTree(argv[1]);
    SearchDirectoryTree(d);
    freeDirectoryTree(d); 
}