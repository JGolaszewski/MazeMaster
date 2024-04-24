#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"
#include "macros.h"
#include "reports.h"

void dispayPath(FILE* Nodes, node_t startNode, USHORT endx, USHORT endy);
void writePathToFile(FILE* Nodes, node_t startNode, USHORT endx, USHORT endy,char* output_file );
