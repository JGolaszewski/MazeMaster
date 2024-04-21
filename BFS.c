#include "BFS.h"


int bfs(FILE* Nodes, USHORT currentx, USHORT currenty, USHORT endx, USHORT endy) {
    
    queue_t queue = create_q();
    node_t cur_node = getNode(Nodes, currentx, currenty);
    node_t nextNode;
    push_q(&queue, cur_node);
    
    while(!queue.isEmpty) {
        cur_node = pop_q(&queue);
        R_DEBUG("Current node: %d %d %d", cur_node.x, cur_node.y, cur_node.data.adj);
		
        if(cur_node.x == endx && cur_node.y == endy) {
			delete_q(&queue);
			return 0;
		}

		if(N_ADJ_LEFT(cur_node)) {
		    nextNode = getNode(Nodes, cur_node.x - 1, cur_node.y);
		    if(nextNode.data.flag == 0) {
		        nextNode.data.parent = RIGHT;
				nextNode.data.flag = 1;
		        setNode(Nodes, nextNode);
				N_DELETE_CONNECTION(nextNode, RIGHT);
		        push_q(&queue, nextNode);
		    }
		}

		if(N_ADJ_RIGHT(cur_node)) {
		    nextNode = getNode(Nodes, cur_node.x + 1, cur_node.y);

		    if(nextNode.data.flag == 0) {
		        nextNode.data.parent = LEFT;
				nextNode.data.flag = 1;
		        setNode(Nodes, nextNode);
				N_DELETE_CONNECTION(nextNode, LEFT);
		        push_q(&queue, nextNode);
		    }
		}

		if(N_ADJ_TOP(cur_node)) {
		    nextNode = getNode(Nodes, cur_node.x, cur_node.y - 1);

		    if(nextNode.data.flag == 0) {
		        nextNode.data.parent = BOTTOM;
				nextNode.data.flag = 1;
		        setNode(Nodes, nextNode);
				N_DELETE_CONNECTION(nextNode, BOTTOM);
		        push_q(&queue, nextNode);
		    }
		}

		if(N_ADJ_BOTTOM(cur_node)) {
		    nextNode = getNode(Nodes, cur_node.x, cur_node.y + 1);

		    if(nextNode.data.flag == 0) {
		        nextNode.data.parent = TOP;
				nextNode.data.flag = 1;
		        setNode(Nodes, nextNode);
				N_DELETE_CONNECTION(nextNode, TOP);
		        push_q(&queue, nextNode);
		    }
		    
		}
    } 
    delete_q(&queue);
	return 1;
}

