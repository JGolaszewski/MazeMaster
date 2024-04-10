#include "graph.h"

node_t getNode(FILE* Nodes, USHORT x, USHORT y) {
    node_t data;
    //BINARY SEARCH IN FILE
    long begin = 0;
    long end = 0;
    fseek(Nodes, 0, SEEK_END);
    end = ftell(Nodes) / sizeof(node_t);

    fseek(Nodes, (begin + (end - begin)/2) * sizeof(node_t), SEEK_SET);

    while(begin <= end) {
        fseek(Nodes, (begin + (end - begin)/2) * sizeof(node_t), SEEK_SET);
        fread(&data, sizeof(node_t), 1, Nodes);
        

        if(data.x == x && data.y == y) return data;
        if(data.y < y || (data.x < x && data.y == y)) begin = (begin + (end - begin)/2) + 1;
        else end = (begin + (end - begin)/2) - 1;
    }
    R_WARNING("(NODE SEARCH) Couldnt find node with coordinates x = %d and y = %d", x, y);
    N_MAKE_INVALID(data);
    return data;
}

int setNode(FILE* Nodes, node_t newData) {
    node_t data;
    //BINARY SEARCH IN FILE
    long begin = 0;
    long end = 0;
    fseek(Nodes, 0, SEEK_END);
    end = ftell(Nodes) / sizeof(node_t);

    fseek(Nodes, (begin + (end - begin)/2) * sizeof(node_t), SEEK_SET);

    while(begin <= end) {
        fseek(Nodes, (begin + (end - begin)/2) * sizeof(node_t), SEEK_SET);
        fread(&data, sizeof(node_t), 1, Nodes);
        
        //WHEN FOUND OVERRIDE WITH NEW DATA
        if(data.x == newData.x && data.y == newData.y) {
            fseek(Nodes, (begin + (end - begin)/2) * sizeof(node_t), SEEK_SET);
            fwrite(&newData, sizeof(node_t), 1, Nodes);
            return 0;
        }
        if(data.y < newData.y || (data.x < newData.x && data.y == newData.y)) begin = (begin + (end - begin)/2) + 1;
        else end = (begin + (end - begin)/2) - 1;
    }
    R_WARNING("(NODE SEARCH) Couldnt find node with coordinates x = %d and y = %d", newData.x, newData.y);
    return 1;
}