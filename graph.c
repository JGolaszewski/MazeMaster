#include "graph.h"

node_t getNode(FILE* Nodes, USHORT x, USHORT y) {
    node_t data;
    fseek(Nodes, 0, SEEK_SET);
    do {
        fread(&data, sizeof(node_t), 1, Nodes);
    } while(!feof(Nodes) && !(data.x == x && data.y == y));
    return data;
}
