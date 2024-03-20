#pragma once

void print_help(char *program_name);
void checkFile(char *name, char **file);
FILE* openFile(const char* filename);
void checkIfNotTheSame(char **in, char **out);
