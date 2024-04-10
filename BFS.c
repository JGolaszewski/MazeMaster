#include "BFS.h"


void bfs(FILE* Nodes, USHORT currentx, USHORT currenty, USHORT endx, USHORT endy) {
    
    queue_t queue = create_q();
    node_t cur_node = getNode(Nodes, currentx, currenty);
    node_t nextNode;
    setNode(Nodes, cur_node);

    push_q(&queue, cur_node);
    
    while(!queue.isEmpty) {
        cur_node = pop_q(&queue);
        R_DEBUG("Current node: %d %d", cur_node.x, cur_node.y);
         if(cur_node.x == endx && cur_node.y == endy)
       	break;
	if(cur_node.flag==0){
	cur_node.flag=1;
	setNode(Nodes, cur_node);
		if(N_ADJ_LEFT(cur_node)) {
		    R_DEBUG("LEFT");
		    nextNode = getNode(Nodes, cur_node.x - 1, cur_node.y);
		    if(nextNode.flag == 0) {
		        R_DEBUG("NOT_VISITED");
		        nextNode.parent = RIGHT;
		        setNode(Nodes, nextNode);
		        push_q(&queue, nextNode);
		       	R_VERBOSE("Added to queue: %d %d", nextNode.x, nextNode.y);
		    }
		}

		if(N_ADJ_RIGHT(cur_node)) {
		    nextNode = getNode(Nodes, cur_node.x + 1, cur_node.y);
		        R_DEBUG("RIGHT");

		    if(nextNode.flag == 0) {
		        R_DEBUG("NOT_VISITED");
		        nextNode.parent = LEFT;
		        setNode(Nodes, nextNode);
		        push_q(&queue, nextNode);
		        R_VERBOSE("Added to queue: %d %d", nextNode.x, nextNode.y);
		    }
		}

		if(N_ADJ_TOP(cur_node)) {
		    nextNode = getNode(Nodes, cur_node.x, cur_node.y - 1);
		        R_DEBUG("TOP");

		    if(nextNode.flag == 0) {
		        R_DEBUG("NOT_VISITED");
		        nextNode.parent = BOTTOM;
		        setNode(Nodes, nextNode);
		        push_q(&queue, nextNode);
		        R_VERBOSE("Added to queue: %d %d", nextNode.x, nextNode.y);
		    }
		}

		if(N_ADJ_BOTTOM(cur_node)) {
		    nextNode = getNode(Nodes, cur_node.x, cur_node.y + 1);
		        R_DEBUG("BOTTOM");

		    if(nextNode.flag == 0) {
		        R_DEBUG("NOT_VISITED");
		        nextNode.parent = TOP;
		        setNode(Nodes, nextNode);
		        push_q(&queue, nextNode);
		        R_VERBOSE("Added to queue: %d %d", nextNode.x, nextNode.y);
		    }
		    
		}
        }
    } 
    delete_q(&queue);
}

