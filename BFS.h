#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "macros.h"
#include "reports.h"
#include "graph.h"

void checkIfvisited(FILE* Nodes, USHORT x, USHORT y,FILE* queue ,node_t current);

bfs(FILE* Nodes, USHORT currentx, USHORT currenty, USHORT endx, USHORT endy);
