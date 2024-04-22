#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "macros.h"
#include "reports.h"
#include "parser.h"

#define N_MAKE_INVALID(node) {node.x = 4095; node.y = 4095;}
#define N_IS_INVALID(node) (node.x == 4095 && node.y == 4095)

#define N_ADJ_LEFT(node) (node.data.adj & 0b1000)
#define N_ADJ_RIGHT(node) (node.data.adj & 0b0100)
#define N_ADJ_TOP(node) (node.data.adj & 0b0010)
#define N_ADJ_BOTTOM(node) (node.data.adj & 0b0001)

#define N_DELETE_CONNECTION(node, dir) (node.data.adj = node.data.adj & ~(1 << (3 - dir)))

enum Direction {
    LEFT = 0b00,
    RIGHT = 0b01,
    TOP = 0b10,
    BOTTOM = 0b11
};

typedef struct NodeData {
    //ADJ - adjacency of node BITS: (LEFT)(RIGHT)(TOP)(BOTTOM)
    UCHAR adj : 4;
    // 00 - LEFT   01 RIGHT  10 - TOP  11 - BOTTOM
    UCHAR parent : 2;
    UCHAR flag : 1;
} nodeData_t;

typedef struct Node {
    USHORT x : 12;
    USHORT y : 12;
    nodeData_t data;
} node_t;

node_t getNode(FILE* Nodes, USHORT x, USHORT y);

//MARKS FLAG IN TEMPFILE AS 1
//TEMP FILE MUST BE OPENED AS "r+"" !!!
int setNode(FILE* Nodes, node_t newData);
