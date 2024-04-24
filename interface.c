#include "interface.h"

void print_help(char *program_name) {
    printf("Usage: %s -i|- -in  <filename> -o|- -out <output> \n", program_name);
    printf("All options :\n");
    printf("  -i|- -in  <filename>       Name of file txt with maze \\n");
    printf("  -o|- -out <output>          File where program should write solution\n");
    printf("  -v|- -verbose        Displaying additional informations\n");
    printf("  -d|- -debug       Debug mode \n");
    printf("  -h|- -help	Help info \n");
    printf("  -q|- -quit \n");
}

void parse_args(int argc, char** argv, char** inFilename, char** outFilename) {
    int opt = 0;
    while ((opt = getopt(argc, argv, "i:o:vdhq")) != -1) {
        switch (opt) {
            case 'i':
                *inFilename = optarg;
                break;
            case 'o':
                *outFilename = optarg;
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
            default:
                exit(EXIT_SUCCESS);
        }
    }
}

FILE* openFile(const char* filename, const char* mode) {
    int idMode = -1;
    USHORT it = 0;

    while(mode[it] != '\0') if(mode[it++] == 'r') idMode = F_OK;
    if(idMode != -1 && access(filename, idMode)) R_ERROR("Couldt open file: %s", filename);

    R_DEBUG("Opening file: %s", filename);

    FILE* f = fopen(filename, mode);
    return f;
}
