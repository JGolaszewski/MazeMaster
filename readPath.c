#include "readPath.h"

void readPath(FILE* Nodes, node_t startNode, USHORT endx, USHORT endy) {
    while (startNode.x!=endx || startNode.y!=endy) {
      
        printf("%d ", startNode.data.parent);
        
        if (startNode.data.parent == LEFT) {
            startNode = getNode(Nodes, startNode.x - 1, startNode.y);
        }
        else if (startNode.data.parent == RIGHT) {
            startNode = getNode(Nodes, startNode.x + 1, startNode.y);
        }
        else if (startNode.data.parent == TOP) {
            startNode = getNode(Nodes, startNode.x, startNode.y - 1);
        }
        else if (startNode.data.parent == BOTTOM) {
            startNode = getNode(Nodes, startNode.x, startNode.y + 1);
        }
 	R_VERBOSE("Going into: %d %d", startNode.x, startNode.y);
 	//if(startNode.x==endx && startNode.y==endy)break;
    }
}

