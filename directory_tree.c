#include "directory_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void SerachDirectoryTreeRec(char* root);

directoryTree* allocate_directoryTree(char *root) {
    directoryTree *directoryTreePtr;

    directoryTreePtr = (directoryTree*)malloc(sizeof(directoryTree));

    directoryTreePtr->root = root;
    directoryTreePtr->fptr = fopen("output", "w");

    return directoryTreePtr;
}

void freeDirectoryTree(directoryTree* directoryTreePtr) {
    fclose(directoryTreePtr->fptr);
    free(directoryTreePtr);
}

void SerachDirectoryTree(directoryTree* directoryTreePtr) {
    SerachDirectoryTreeRec(directoryTreePtr->root);
}

void SerachDirectoryTreeRec(char* root) {
    char path[MAX_PATH];
    strcpy(path, root);
    strcat(path, "\\*");
    printf("SerachDirectoryTreeRec, root is: %s\n", root);
    HANDLE hFind;
    WIN32_FIND_DATA FindFileData;

    hFind = FindFirstFile(path, &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf ("FindFirstFile failed (%d)\n", GetLastError());
    } else {
        do {
            if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
                if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
                    char *subDirPath = (char*)malloc(sizeof(char)*(strlen(root)+strlen(FindFileData.cFileName)+1));
                    strcpy(subDirPath, root);
                    strcat(strcat(subDirPath, "\\"), FindFileData.cFileName);
                    SerachDirectoryTreeRec(subDirPath);
                } else {
                    printf("%s\n", FindFileData.cFileName);
                }
            }
        } while (FindNextFile(hFind, &FindFileData));

        if (GetLastError() != ERROR_NO_MORE_FILES) {
            printf ("FindNextFile failed (%d)\n", GetLastError());
        } 
    }

    cleanup:
    FindClose(hFind);
    return;
}