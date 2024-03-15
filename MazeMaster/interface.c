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

    printf("Please give file %s: ", name);
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


FILE* openFile(const char* filename) {
    char* dynamicFilename = strdup(filename); 
    if (dynamicFilename == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(dynamicFilename, "r");
    while (file == NULL) {
        printf("File \"%s\" does not exist. Please provide another file:\n", dynamicFilename);
        scanf("%s", dynamicFilename);
 	  while (strcmp(dynamicFilename + strlen(dynamicFilename) - 4, ".txt") != 0) {
        printf("The file must have a \".txt\" extension. Please provide a valid file: ");
        scanf("%s", dynamicFilename);
        }
        file = fopen(dynamicFilename, "r");
        
        
    }


    dynamicFilename = realloc(dynamicFilename, (strlen(dynamicFilename) + 1) * sizeof(char));
    if (dynamicFilename == NULL) {
        printf("Memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }

    return file;
}

void checkIfNotTheSame(char **in, char **out) {
    if (strcmp(*in, *out) == 0) {
        printf("The input files are the same.\n");
        printf("%d. input\n",1);
        printf("%d. output\n",2);
        printf("Which string do you want to change? (Enter number: 1 or 2): ");
        
        int choice;
        scanf("%d", &choice);
        
        if (choice == 1) {
           *in=NULL;
           checkFile("input",in);
        } else if (choice == 2) {
            *out=NULL;
           checkFile("input",out);
        } else {
            printf("Invalid choice.\n");
        }
    }
}
