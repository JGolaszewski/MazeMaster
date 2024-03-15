#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "macros.h"

void readLineBit(FILE* in, char** outBuffer, USHORT* size);
void toGraph(FILE* out, const char* buffers[3], const USHORT lineSize, const USHORT height);
void parseFile(const char* filename);