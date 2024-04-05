#pragma once

#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>

#include "macros.h"
#include "reports.h"

void print_help(char *program_name);
char* pathRelative(char* relativePath);
FILE* openFile(const char* filename, const char* mode);
