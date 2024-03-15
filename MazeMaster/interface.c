#include <stdio.h>
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

/*void checkIfProperArg(int arg, char *filename[], char *output[]) {

}*/
