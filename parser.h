#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "interface.h"
#include "graph.h"
#include "macros.h"

extern USHORT mazeWidth;

extern USHORT startX;
extern USHORT startY;

extern USHORT endX;
extern USHORT endY;

void readLineBit(FILE* in, char** outBuffer, USHORT* size);
void toGraph(FILE* tempF, const char* buffers[3], const USHORT lineSize, const USHORT height);
void parseFile(const char* filename);