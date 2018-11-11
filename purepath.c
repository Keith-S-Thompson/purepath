#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void) {
    const char *path = getenv("PATH");
    if (path == NULL) {
        fprintf(stderr, "$PATH is not set\n");
        exit(EXIT_FAILURE);
    }

    const size_t pathlen = strlen(path);

    char *const path2 = malloc(pathlen + 1);
    if (path2 == NULL) {
        exit(EXIT_FAILURE);
    }
    strcpy(path2, path);

    size_t element_count = 1;
    for (char *p = path2; *p != '\0'; p ++) {
        if (*p == ':') {
            element_count ++;
            *p = '\0';
        }
    }
    char **elements = malloc(element_count * sizeof *elements);
    if (elements == NULL) {
        free(path2);
        exit(EXIT_FAILURE);
    }
    int elem_index = 0;
    for (size_t i = 0; i < pathlen; i ++) {
        if (i == 0 || path2[i-1] == '\0') {
            elements[elem_index++] = path2+i;
        }
    }

    for (size_t i = 0; i < element_count; i ++) {
        for (size_t j = 0; j < i; j ++) {
            if (strcmp(elements[i], elements[j]) == 0) {
                elements[i] = NULL;
                break;
            }
        }
    }

    int first = 1;
    for (size_t i = 0; i < element_count; i ++) {
        if (elements[i] != NULL) {
            if (first) {
                first = 0;
            }
            else {
                putchar(':');
            }
            fputs(elements[i], stdout);
        }
    }
    putchar('\n');

    free(path2);
    free(elements);
}
