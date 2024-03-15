#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "interface.h"

/*size_t countLines(FILE* f) {
    size_t count = 0;
    char line [1024];
    while(fgets(&line, 1024, f)) count++;
    rewind(f);
    return count;
}*/

int main(int argc, char** argv) {

int opt;
    char *input_file = NULL;
    char *output_file = NULL;
    int verbose = 0;
    int debug = 0;

    while ((opt = getopt(argc, argv, "i:o:vdhq")) != -1) {
        switch (opt) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'd':
                debug = 1;
                break;
            case 'h':
                print_help(argv[0]);
                exit(EXIT_SUCCESS);
            case 'q':
                printf("Exiting program...\n");
                exit(EXIT_SUCCESS);
            default: /* '?' */
                fprintf(stderr, "Usage: %s -i <input_file> -o <output_file> [-v] [-d] [-h] [-q]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }


    printf("Input file: %s\n", input_file);
    printf("Output file: %s\n", output_file);
    printf("Verbose mode: %s\n", verbose ? "enabled" : "disabled");
    printf("Debug mode: %s\n", debug ? "enabled" : "disabled");


/*

    FILE* f = fopen("../in/maze.txt", "r");
    if(!f) return -1;

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    size_t chunkSize = size / 16;

    rewind(f);

    char* chunk = malloc(sizeof(char) * chunkSize);
    if(!chunk) return -1;
    char ch = ' ';
    size_t s = countLines(f);

    printf("%d %d", (int)s, (int)((size-s)/s));*/
    return 0;
}
