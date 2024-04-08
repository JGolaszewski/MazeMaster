#include "BFS.h"


void checkIfvisited(FILE* Nodes, USHORT x, USHORT y,FILE* queue ,node_t current){
	node_t temp = getNode (Nodes,x, y);
	makeParent(Nodes, x, y, current.x, current.y);
	if(temp.flag==0){
 		fprintf(queue ,"%d %d " , temp.x, temp.y );

	}
}


bfs(FILE* Nodes, USHORT currentx, USHORT currenty, USHORT endx, USHORT endy){
	
 	FILE* queue;
 	queue = fopen("tempQueue.txt", "r+");
 	bool found=0;
 	node_t current= getNode (Nodes,currentx, currenty);
 	makeParent(Nodes, currentx, currenty, 0, 0);
 	int itr =1; 
 	fprintf(queue ,"%d %d" , current.x ,current.y );	
 	
 	while(!found){
 		fscanf(queue,"%d", &currentx);
 		fscanf(queue,"%d", &currenty);
 		 
 		current = getNode (Nodes,currentx, currenty);
		
 		if ( current.flag==0){
 		 	markNode( Nodes, currentx, currenty);
 		if(N_ADJ_RIGHT(current)){
			checkIfvisited(Nodes, current.x+1 , current.y ,queue, current);
			
 		}
 		if(N_ADJ_LEFT(current)){
 			checkIfvisited(Nodes, current.x-1 , current.y ,queue, current );
 		}
 		if(N_ADJ_TOP(current)){
 		 	checkIfvisited(Nodes, current.x , current.y+1 , queue, current );
 		}
 		if(N_ADJ_BOTTOM(current)){
 		 	checkIfvisited(Nodes, current.x , current.y-1 , queue,current );
 		}
 		if(current.x==endx && current.x==endx){
		found=1;
		}
	
 		}
 	}
 	free(queue);

}

