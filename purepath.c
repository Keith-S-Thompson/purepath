#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void usage_error(const char *program_name) {
    fprintf(stderr, "Usage: %s [-k] [-c] [-C] [path]\n", program_name);
    fprintf(stderr, "    -k Keep non-directory entries\n");
    fprintf(stderr, "    -c Remove entries starting with \"/cygdrive/\"\n");
    fprintf(stderr, "    -C Remove entries starting with \"/cygdrive/\"\n");
    fprintf(stderr, "       iff $DELETE_CYGDRIVE_FROM_PATH is set\n");
    fprintf(stderr, "With no path argument, use $PATH\n");
    exit(EXIT_FAILURE);
}

static void malloc_failure(const char *message) {
    fprintf(stderr, "malloc failed for %s\n", message);
    exit(EXIT_FAILURE);
}

static bool is_directory(const char *dirname) {
    struct stat buf;
    const int stat_result = stat(dirname, &buf);
    return stat_result == 0 && (buf.st_mode & S_IFMT) == S_IFDIR;
}

int main(int argc, char **argv) {
    // TODO: Use getopt
    bool keep_all = false;
    bool remove_cygdrive = false;
    while (argc > 1) {
        if (strcmp(argv[1], "-k") == 0) {
            keep_all = true;
            argc--;
            argv++;
        }
        else if (strcmp(argv[1], "-c") == 0) {
            remove_cygdrive = true;
            argc--;
            argv++;
        }
        else if (strcmp(argv[1], "-C") == 0) {
            if (getenv("DELETE_CYGDRIVE_FROM_PATH") != NULL) {
                remove_cygdrive = true;
            }
            argc--;
            argv++;
        }
        else {
            break;
        }
    }
    const char *path;
    switch (argc) {
        case 1:
            path = getenv("PATH");
            if (path == NULL) {
                fprintf(stderr, "$PATH is not set\n");
                usage_error(argv[0]);
            }
            break;
        case 2:
            path = argv[1];
            if (path[0] == '-') {
                usage_error(argv[0]);
            }
            break;
        default:
            usage_error(argv[0]);
            break;
    }

    const size_t pathlen = strlen(path);

    char *const path2 = malloc(pathlen + 1);
    if (path2 == NULL) {
        malloc_failure("path2");
    }
    strcpy(path2, path);

    size_t element_count = 1;
    for (size_t i = 0; i < pathlen; i ++) {
        if (path2[i] == ':') {
            element_count ++;
            path2[i] = '\0';
        }
    }
    char const **const elements = malloc(element_count * sizeof *elements);
    if (elements == NULL) {
        free(path2);
        malloc_failure("elements");
    }
    size_t elem_index = 0;
    for (size_t i = 0; i <= pathlen; i ++) {
        if (i == 0 || path2[i-1] == '\0') {
            elements[elem_index++] = path2+i;
        }
    }

    for (size_t i = 0; i < element_count; i ++) {
        for (size_t j = 0; j < i; j ++) {
            if (elements[j] != NULL && strcmp(elements[i], elements[j]) == 0) {
                elements[i] = NULL;
                break;
            }
        }
    }

    bool first = true;
    for (size_t i = 0; i < element_count; i ++) {
        if (elements[i] != NULL) {
            // printf(">>> elements[%zu]=%s\n", i, elements[i]);
            bool keep = true;
            if (! keep_all && ! is_directory(elements[i])) {
                keep = false;
            }
            else if (remove_cygdrive && strstr(elements[i], "/cygdrive/") != NULL) {
                keep = false;
            }
            // printf("    keep=%s\n", keep ? "true" : "false");
            if (keep) {
                if (!first) {
                    putchar(':');
                }
                fputs(elements[i], stdout);
                first = false;
            }
        }
    }
    putchar('\n');

    free(path2);
    free(elements);
}
