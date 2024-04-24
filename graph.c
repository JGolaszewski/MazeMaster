#include "graph.h"

node_t getNode(FILE* Nodes, USHORT x, USHORT y) {
    node_t data;
    fseek(Nodes, (x + y * mazeWidth) * sizeof(nodeData_t), SEEK_SET);
    if(feof(Nodes)) {
        R_WARNING("(NODE SEARCH) Couldnt find node with coordinates x = %d and y = %d", x, y);
        N_MAKE_INVALID(data);
        return data;
    }
    fread(&data.data, sizeof(nodeData_t), 1, Nodes);
    data.x = x;
    data.y = y;
    return data;
}

int setNode(FILE* Nodes, node_t newData) {
    fseek(Nodes, (newData.x + newData.y * mazeWidth) * sizeof(nodeData_t), SEEK_SET);
    if(feof(Nodes)) {
        R_WARNING("(NODE SEARCH) Couldnt find node with coordinates x = %d and y = %d", newData.x, newData.y);
        return 1;
    }
    fwrite(&newData.data, sizeof(nodeData_t), 1, Nodes);
    return 0;
}