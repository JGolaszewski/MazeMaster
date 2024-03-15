#pragma once
#include "macros.h"

typedef struct Edge {
    USHORT x : 10;
    USHORT y : 10;
    USHORT visited : 1;
} edge_t;