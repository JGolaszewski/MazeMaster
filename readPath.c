#include "readPath.h"

void readPath(FILE* Nodes, node_t startNode, USHORT endx, USHORT endy) {
    while (startNode.x!=endx && startNode.x!=endy) {
      
        printf("%d ", startNode.parent);
        
        if (startNode.parent == LEFT) {
            startNode = getNode(Nodes, startNode.x - 1, startNode.y);
        }
        else if (startNode.parent == RIGHT) {
            startNode = getNode(Nodes, startNode.x + 1, startNode.y);
        }
        else if (startNode.parent == TOP) {
            startNode = getNode(Nodes, startNode.x, startNode.y - 1);
        }
        else if (startNode.parent == BOTTOM) {
            startNode = getNode(Nodes, startNode.x, startNode.y + 1);
        }
 	R_VERBOSE("Going into: %d %d", startNode.x, startNode.y);
 	
    }
}

