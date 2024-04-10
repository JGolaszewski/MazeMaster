#include "readPath.h"

void readPath(FILE* Nodes, node_t startNode){
	while(1){
		printf("&c ", startNode.parent);
		if(startNode.parent==LEFT){
		startNode=getNode(Nodes, startNode.x-1, startNode.y);
		}
		else if (startNode.parent==RIGHT){
		startNode=getNode(Nodes, startNode.x+1, startNode.y);
		}
		else if (startNode.parent==TOP){
		startNode=getNode(Nodes, startNode.x, startNode.y+1);
		}
		else if (startNode.parent==BOTTOM){
		startNode=getNode(Nodes, startNode.x, startNode.y-1);
		}
		else if (startNode.parent==NULL)break;
	}
}
