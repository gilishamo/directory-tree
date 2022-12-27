#include <stdlib.h>
#include <stdio.h>

void traceAndExit(int statusCode, char* message) {
    printf("ERROR: %s\n", message);
    exit(statusCode);
}