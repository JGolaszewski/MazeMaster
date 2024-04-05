#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"

typedef struct Node {
    USHORT x : 12;
    USHORT y : 12;
    UCHAR adj : 4;
} node_t;

node_t getNode(FILE* Nodes, USHORT x, USHORT y);