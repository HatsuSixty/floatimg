#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfloatimg.h"

void usage(FILE* stream, const char* program_name) {
    fprintf(stream, "Usage: %s [FLAGS] <IMAGE>\n", program_name);
    fprintf(stream, "  FLAGS:\n");
    fprintf(stream, "    --help | -h          Show this help and exit with 0 code\n");
    fprintf(stream, "  IMAGE:\n");
    fprintf(stream, "    The image that is going to be displayed\n");
}

int main(int argc, const char** argv) {
    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough arguments were provided\n");
        usage(stderr, argv[0]);
        exit(1);
    }

    const char* file_path;

    for (int i = 1; i < argc; ++i) {
        if ((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "--h") == 0)) {
            usage(stdout, argv[0]);
            exit(0);
        } else {
            file_path = argv[i];
        }
    }

    floatimg(file_path);

    return 0;
}
