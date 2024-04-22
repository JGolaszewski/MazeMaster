#pragma once

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <linux/limits.h>

#include "macros.h"
#include "reports.h"

void print_help(char *program_name);
void parse_args(int argc, char** argv, char** inFilename, char** outFilename);
FILE* openFile(const char* filename, const char* mode);
