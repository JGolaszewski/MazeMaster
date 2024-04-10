#include "BFS.h"


void checkIfvisited(FILE* Nodes, USHORT x, USHORT y,FILE* queue ,node_t current){
	node_t temp = getNode (Nodes,x, y);
	if(temp.flag==0){
 		fprintf(queue ,"%d %d " , temp.x, temp.y );
 		//makeParent(Nodes, x, y, current.x, current.y);

	}
}


void bfs(FILE* Nodes, USHORT currentx, USHORT currenty, USHORT endx, USHORT endy) {
    queue_t queue = create_q();
    node_t cur_node = getNode(Nodes, currentx, currenty);
    node_t nextNode;
    cur_node.flag = 1;
    setNode(Nodes, cur_node);

    nextNode.x = cur_node.x;
    nextNode.y = cur_node.y;
    nextNode.adj = cur_node.adj;
    nextNode.flag = 1;
    nextNode.parent = cur_node.parent;


    push_q(&queue, cur_node);
    do {
        R_DEBUG("Current node: %d %d", cur_node.x, cur_node.y);

        if(N_ADJ_LEFT(cur_node)) {
            R_DEBUG("LEFT");
            nextNode = getNode(Nodes, cur_node.x - 1, cur_node.y);
            if(nextNode.flag == 0) {
                R_DEBUG("VALID");
                nextNode.parent = RIGHT;
                setNode(Nodes, nextNode);
                push_q(&queue, nextNode);
            }
        }

        if(N_ADJ_RIGHT(cur_node)) {
            nextNode = getNode(Nodes, cur_node.x + 1, cur_node.y);
                R_DEBUG("RIGHT");

            if(nextNode.flag == 0) {
                R_DEBUG("VALID");
                nextNode.parent = LEFT;
                setNode(Nodes, nextNode);
                push_q(&queue, nextNode);
            }
        }

        if(N_ADJ_TOP(cur_node)) {
            nextNode = getNode(Nodes, cur_node.x, cur_node.y - 1);
                R_DEBUG("TOP");

            if(nextNode.flag == 0) {
                R_DEBUG("VALID");
                nextNode.parent = BOTTOM;
                setNode(Nodes, nextNode);
                push_q(&queue, nextNode);
            }
        }

        if(N_ADJ_BOTTOM(cur_node)) {
            nextNode = getNode(Nodes, cur_node.x, cur_node.y + 1);
                R_DEBUG("BOTTOM");

            if(nextNode.flag == 0) {
                R_DEBUG("VALID");
                nextNode.parent = TOP;
                setNode(Nodes, nextNode);
                push_q(&queue, nextNode);
            }
        }
        //sleep(1);
        cur_node = pop_q(&queue);
    } while(!queue.isEmpty && !(cur_node.x == endx && cur_node.y == endy));
    delete_q(&queue);
}

