#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "interface.h"
#include "graph.h"
#include "macros.h"

#define FILE_SIGNATURE 0x52524243
#define ESCAPE_CODE 0x1B

typedef struct FileHeader {
    USHORT columns : 16;
    USHORT lines : 16;
    USHORT startX : 16;
    USHORT startY : 16;
    USHORT endX : 16;
    USHORT endY : 16;
    int reserved1 : 32;
    int reserved2 : 32;
    int reserved3 : 32;
    UINT counter : 32; //Number of code words
    UINT solutionOffset : 32;
    char separator : 8;
    char wall : 8;
    char path : 8;
} fileHeader_h;

typedef struct CodeWords {
    char separator : 8;
    char value : 8;
    UCHAR count : 8;
} codeWord_t;

extern UCHAR isBinary;
extern fileHeader_h fileData;

void readLineBit(FILE* in, char** outBuffer);
void binReadLineBit(FILE* in, char** outBuffer);
void toGraph(FILE* tempF, char* buffers[3], const USHORT height);
USHORT preParser(FILE* file);
void parseFile(const char* filename);