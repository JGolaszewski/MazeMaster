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
        
        R_DEBUG("(NODE SEARCH) x = %d, y = %d, adj = %d", data.x, data.y, data.adj);

        if(data.x == x && data.y == y) return data;
        if(data.y < y || (data.x < x && data.y == y)) begin = (begin + (end - begin)/2) + 1;
        else end = (begin + (end - begin)/2) - 1;
    }
    R_WARNING("(NODE SEARCH) Couldnt find node with coordinates x = %d and y = %d", x, y);
    N_MAKE_INVALID(data);
    return data;
}

node_t markNode(FILE* Nodes, USHORT x, USHORT y) {
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
        
        R_DEBUG("(NODE SEARCH) x = %d, y = %d, adj = %d", data.x, data.y, data.adj);
        //WHEN FOUND OVERRIDE WITH NEW DATA
        if(data.x == x && data.y == y) {
            fseek(Nodes, (begin + (end - begin)/2) * sizeof(node_t), SEEK_SET);
            data.flag = 0b1;
            fwrite(&data, sizeof(node_t), 1, Nodes);
        }
        if(data.y < y || (data.x < x && data.y == y)) begin = (begin + (end - begin)/2) + 1;
        else end = (begin + (end - begin)/2) - 1;
    }
}


void  makeParent(FILE* Nodes, USHORT x, USHORT y, USHORT prevx, USHORT prevy){
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
        
        R_DEBUG("(NODE SEARCH) x = %d, y = %d, adj = %d", data.x, data.y, data.adj);
        //WHEN FOUND OVERRIDE WITH NEW DATA
        if(data.x == x && data.y == y) {
            fseek(Nodes, (begin + (end - begin)/2) * sizeof(node_t), SEEK_SET);
            data.prevx = prevx;
            data.prevy = prevy;
            fwrite(&data, sizeof(node_t), 1, Nodes);
        }
        if(data.y < y || (data.x < x && data.y == y)) begin = (begin + (end - begin)/2) + 1;
        else end = (begin + (end - begin)/2) - 1;
    }
}
