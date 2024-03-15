#pragma once

//PROBLEM SPECIFICATION
#define MAX_LINE_WIDTH 2049
#define WALL_CHAR 'X'

//TYPE MAKRO
#define USHORT unsigned short
#define UCHAR unsigned 

//NAME MAKRO
#define TEMP_NODE_FILENAME "../temp/tempNodes.txt"

//FILE FORMATTING
#define TEMP_NODE_FORMAT(x, y, flag) "%d %d %d\n", (x), (y), (flag)

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