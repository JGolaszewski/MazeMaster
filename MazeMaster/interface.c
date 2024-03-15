#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

void checkFile(char *name, char **file) {

    if (*file == NULL) {
        *file = (char *)malloc(100 * sizeof(char)); 
        if (*file == NULL) {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Please give file \"%s\": ", name);
    scanf("%s", *file);


    while (strcmp(*file + strlen(*file) - 4, ".txt") != 0) {
        printf("The file must have a \".txt\" extension. Please provide a valid file: ");
        scanf("%s", *file);
    }


    *file = (char *)realloc(*file, (strlen(*file) + 1) * sizeof(char));
    if (*file == NULL) {
        printf("Memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }
}
