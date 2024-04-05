#include "interface.h"

void print_help(char *program_name) {
    printf("Usage: %s -i|- -in  <filename> -o|- -out <output> \n");
    printf("All options :\n");
    printf("  -i|- -in  <filename>       Name of file txt with maze \\n");
    printf("  -o|- -out <output>          File where program should write solution\n");
    printf("  -v|- -verbose        Displaying additional informations\n");
    printf("  -d|- -debug       Debug mode \n");
    printf("  -h|- -help	Help info \n");
    printf("  -q|- -quit \n");
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
