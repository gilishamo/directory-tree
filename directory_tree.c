#include "directory_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "utils.h"

// forward declaration
void SearchDirectoryTreeRec(directoryTree *directoryTreePtr, char* root);

directoryTree* allocate_directoryTree(char *root) {
    directoryTree *directoryTreePtr;

    directoryTreePtr = (directoryTree*)malloc(sizeof(directoryTree));
    if (directoryTreePtr == NULL) {
        traceAndExit(1, "failed to allocate memmory");
    }

    directoryTreePtr->root = root;

    directoryTreePtr->fptr = fopen("output", "w+");
    if (directoryTreePtr->fptr == NULL) {
        traceAndExit(2, "failed to open file");
    }

    return directoryTreePtr;
}

void freeDirectoryTree(directoryTree* directoryTreePtr) {
    fclose(directoryTreePtr->fptr);
    free(directoryTreePtr);
}

void WriteDirNameToFile(directoryTree* directoryTreePtr, char* dir) {
    fputs(dir, directoryTreePtr->fptr);
    fputs("\n", directoryTreePtr->fptr);
}

void WriteFileNameToFile(directoryTree* directoryTreePtr, char* file) {
    fputs("\t", directoryTreePtr->fptr);
    fputs(file, directoryTreePtr->fptr);
    fputs("\n", directoryTreePtr->fptr);
}

void SearchDirectoryTree(directoryTree* directoryTreePtr) {
    SearchDirectoryTreeRec(directoryTreePtr, directoryTreePtr->root);
}

void SearchDirectoryTreeRec(directoryTree* directoryTreePtr, char* root) {
    char path[MAX_PATH];
    strcpy(path, root);
    strcat(path, "\\*");
    printf("SerachDirectoryTreeRec, root is: %s\n", root);
    HANDLE hFind;
    WIN32_FIND_DATA FindFileData;

    WriteDirNameToFile(directoryTreePtr, root);

    hFind = FindFirstFile(path, &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf ("FindFirstFile failed (%d)\n", GetLastError());
        goto cleanup;
    }

    do {
        if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
            if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
                char *subDirPath = (char*)malloc(sizeof(char)*(strlen(root)+strlen(FindFileData.cFileName)+1));
                strcpy(subDirPath, root);
                strcat(strcat(subDirPath, "\\"), FindFileData.cFileName);
                SearchDirectoryTreeRec(directoryTreePtr, subDirPath);
            } else {
                printf("%s\n", FindFileData.cFileName);
                WriteFileNameToFile(directoryTreePtr, FindFileData.cFileName);
            }
        }
    } while (FindNextFile(hFind, &FindFileData));

    if (GetLastError() != ERROR_NO_MORE_FILES) {
        printf ("FindNextFile failed (%d)\n", GetLastError());
    } 
    

    cleanup:
    FindClose(hFind);
    return;
}