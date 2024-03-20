#pragma once

//PROBLEM SPECIFICATION
#define MAX_LINE_WIDTH 2049
#define WALL_CHAR 'X'

//TYPE MAKRO
#define UINT unsigned int
#define USHORT unsigned short
#define UCHAR unsigned char

//NAME MAKRO
#define TEMP_NODE_FILENAME "../temp/tempNodes.txt"
#define TEMP_MATRIX_FILENAME "../temp/tempMatrix.txt"

//FILE FORMATTING
//Data:
//id - id of node
//x - coordinate
//y - coordinate
//Additional flag binary: First 4 bits(Additional info), Last 4 bits(Connection: (LEFT)(RIGHT)(TOP)(BOTTOM))
#define TEMP_NODE_FORMAT(id, x, y, flag) "%d %d %d %d\n", (id), (x), (y), (flag)

//BIT OPERATIONS MAKRO
#define GET_BIT(byteArr, n) \
  (((byteArr)[(n)/8]>>(7-((n)%8)))&0x01)

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

#define PRINT_BINARY(byte) printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(byte))