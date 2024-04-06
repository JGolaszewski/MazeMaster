#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "macros.h"
#include "reports.h"

#define N_MAKE_INVALID(node) {node.x = USHRT_MAX; node.y = USHRT_MAX; node.adj = UCHAR_MAX;}
#define N_IS_INVALID(node) (node.x == USHRT_MAX && node.y == USHRT_MAX && node.adj = UCHAR_MAX)

typedef struct Node {
    USHORT x : 12;
    USHORT y : 12;
    UCHAR adj : 4;
} node_t;

node_t getNode(FILE* Nodes, USHORT x, USHORT y);