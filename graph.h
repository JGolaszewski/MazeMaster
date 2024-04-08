#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "macros.h"
#include "reports.h"

#define N_MAKE_INVALID(node) {node.x = USHRT_MAX; node.y = USHRT_MAX; node.adj = UCHAR_MAX;}
#define N_IS_INVALID(node) (node.x == USHRT_MAX && node.y == USHRT_MAX && node.adj = UCHAR_MAX)

#define N_ADJ_LEFT(node) (node.adj & 0b1000)
#define N_ADJ_RIGHT(node) (node.adj & 0b0100)
#define N_ADJ_TOP(node) (node.adj & 0b0010)
#define N_ADJ_BOTTOM(node) (node.adj & 0b0001)



typedef struct Node {
    USHORT x : 12;
    USHORT y : 12;
    //ADJ - adjacency of node BITS: (LEFT)(RIGHT)(TOP)(BOTTOM)
    UCHAR adj : 4;
    UCHAR flag : 1;
    USHORT prevx : 12;
    USHORT prevy : 12;
} node_t;

node_t getNode(FILE* Nodes, USHORT x, USHORT y);
//MARKS FLAG IN TEMPFILE AS 1
//TEMP FILE MUST BE OPENED AS "r+"" !!!
node_t markNode(FILE* Nodes, USHORT x, USHORT y);
void  makeParent(FILE* Nodes, USHORT x, USHORT y, USHORT prevx, USHORT prevy);
