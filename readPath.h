#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"
#include "macros.h"
#include "reports.h"
#include "macros.h"
#include "parser.h"

void writePathToFile(FILE* Nodes, node_t startNode, USHORT endx, USHORT endy,char* output_file );
void writePathToBinary(FILE* Nodes, node_t startNode, USHORT endx, USHORT endy, char* output_file );
void displayPath(FILE* Nodes, node_t startNode, USHORT endx, USHORT endy);
