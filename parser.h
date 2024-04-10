#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "graph.h"
#include "macros.h"

static FILE* ftemp;

void readLineBit(FILE* in, char** outBuffer, USHORT* size);
void toGraph(FILE* tempF, const char* buffers[3], const USHORT lineSize, const USHORT height);
void parseFile(const char* filename);