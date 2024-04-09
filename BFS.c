#include "BFS.h"


void checkIfvisited(FILE* Nodes, USHORT x, USHORT y,FILE* queue ,node_t current){
	node_t temp = getNode (Nodes,x, y);
	if(temp.flag==0){
 		fprintf(queue ,"%d %d " , temp.x, temp.y );
 		makeParent(Nodes, x, y, current.x, current.y);

	}
}


void bfs(FILE* Nodes, USHORT currentx, USHORT currenty, USHORT endx, USHORT endy) {
    FILE* queue;
    queue = fopen("tempQueue.txt", "r+");
    if (queue == NULL) {
        R_ERROR("Error opening file");
        
        return;
    }
    
    bool found = false;
    node_t current = getNode(Nodes, currentx, currenty);
    fprintf(queue, "%d %d", current.x, current.y);

    while (!found) {
        if (fscanf(queue, "%d %d", &currentx, &currenty) != 2) {
            R_ERROR("Failed to read coordinates, possibly end of file reached");
            break;
        }

        current = getNode(Nodes, currentx, currenty);

        if (current.flag == 0) {
            markNode(Nodes, currentx, currenty);
            if (N_ADJ_RIGHT(current)) {
                checkIfvisited(Nodes, current.x + 1, current.y, queue, current);
            }
            if (N_ADJ_LEFT(current)) {
                checkIfvisited(Nodes, current.x - 1, current.y, queue, current);
            }
            if (N_ADJ_TOP(current)) {
                checkIfvisited(Nodes, current.x, current.y + 1, queue, current);
            }
            if (N_ADJ_BOTTOM(current)) {
                checkIfvisited(Nodes, current.x, current.y - 1, queue, current);
            }
            if (current.x == endx && current.y == endy) {
                found = true;
            }
        }
    }
    
    fclose(queue);
}

