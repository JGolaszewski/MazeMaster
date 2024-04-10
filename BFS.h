#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "macros.h"
#include "reports.h"
#include "graph.h"
#include "interface.h"
#include "queue.h"

void checkIfvisited(FILE* Nodes, USHORT x, USHORT y,FILE* queue ,node_t current);

void bfs(FILE* Nodes, USHORT currentx, USHORT currenty, USHORT endx, USHORT endy);
