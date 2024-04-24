#include "readPath.h"

void displayPath(FILE* Nodes, node_t startNode, USHORT endx, USHORT endy) {
 	
int forward = 0;
    node_t lastNode;
    R_VERBOSE("Reading path started..");
    printf("START\n");
    while (startNode.x!=endx || startNode.y!=endy) {
      	lastNode= startNode;
      	forward++;        
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
        
        
	
	if(startNode.data.parent == lastNode.data.parent  && lastNode.data.parent == BOTTOM){
		continue;
	}
	else if (startNode.data.parent == LEFT && lastNode.data.parent == TOP){
		printf("FORWARD %d\n", forward);
		printf("TURNLEFT\n");
		forward =0 ;
	}else if(startNode.data.parent == BOTTOM && lastNode.data.parent == LEFT){
		printf("FORWARD %d\n", forward);
		printf("TURNLEFT\n");
		forward =0 ;
	}else if(startNode.data.parent == RIGHT && lastNode.data.parent == BOTTOM){
		printf("FORWARD %d\n", forward);
		printf("TURNLEFT\n");
		forward =0 ;
	}else if(startNode.data.parent == TOP && lastNode.data.parent == RIGHT){
		printf("FORWARD %d\n", forward);
		printf("TURNLEFT\n");
		forward =0 ;
	}else if(startNode.data.parent == RIGHT && lastNode.data.parent == TOP){
		printf("FORWARD %d\n", forward);
		printf("TURNRIGHT\n");
		forward =0 ;
	}else if(startNode.data.parent == BOTTOM && lastNode.data.parent == RIGHT){
		printf("FORWARD %d\n", forward);
		printf("TURNRIGHT\n");
		forward =0 ;
	}else if(startNode.data.parent == LEFT && lastNode.data.parent == BOTTOM){
		printf("FORWARD %d\n", forward);
		printf("TURNRIGHT\n");
		forward =0 ;
	}else if(startNode.data.parent == TOP && lastNode.data.parent == LEFT){
		printf("FORWARD %d\n", forward);
		printf("TURNRIGHT\n");
		forward =0 ;
        };

 	 R_DEBUG("Going into: %d %d", startNode.x, startNode.y);
 	

    }
   printf("STOP\n");
   R_VERBOSE("Path is ready");
}

#include "readPath.h"

void writePathToFile(FILE* Nodes, node_t startNode, USHORT endx, USHORT endy,char* output_file ) {
 	
int forward = 0;
    node_t lastNode;
    FILE *output=openFile(output_file ,"w");
    R_VERBOSE("Opening file to write...");
    fprintf(output,"START\n");
    R_VERBOSE("Start writing to file");
    while (startNode.x!=endx || startNode.y!=endy) {
      	lastNode= startNode;
      	forward++;        
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
        
        
	
	if(startNode.data.parent == lastNode.data.parent && lastNode.data.parent == BOTTOM){
		continue;
	}
	else if (startNode.data.parent == LEFT && lastNode.data.parent == TOP){
		fprintf(output,"FORWARD %d\n", forward);
		fprintf(output,"TURNLEFT\n");
		forward =0 ;
	}else if(startNode.data.parent == BOTTOM && lastNode.data.parent == LEFT){
		fprintf(output,"FORWARD %d\n", forward);
		fprintf(output,"TURNLEFT\n");
		forward =0 ;
	}else if(startNode.data.parent == RIGHT && lastNode.data.parent == BOTTOM){
		fprintf(output,"FORWARD %d\n", forward);
		fprintf(output,"TURNLEFT\n");
		forward =0 ;
	}else if(startNode.data.parent == TOP && lastNode.data.parent == RIGHT){
		fprintf(output,"FORWARD %d\n", forward);
		fprintf(output,"TURNLEFT\n");
		forward =0 ;
	}else if(startNode.data.parent == RIGHT && lastNode.data.parent == TOP){
		fprintf(output,"FORWARD %d\n", forward);
		fprintf(output,"TURNRIGHT\n");
		forward =0 ;
	}else if(startNode.data.parent == BOTTOM && lastNode.data.parent == RIGHT){
		fprintf(output,"FORWARD %d\n", forward);
		fprintf(output,"TURNRIGHT\n");
		forward =0 ;
	}else if(startNode.data.parent == LEFT && lastNode.data.parent == BOTTOM){
		fprintf(output,"FORWARD %d\n", forward);
		fprintf(output,"TURNRIGHT\n");
		forward =0 ;
	}else if(startNode.data.parent == TOP && lastNode.data.parent == LEFT){
		fprintf(output,"FORWARD %d\n", forward);
		fprintf(output,"TURNRIGHT\n");
		forward =0 ;
        };
	 R_DEBUG("Going into: %d %d", startNode.x, startNode.y);
 	

    }
   fprintf(output,"STOP\n");
   fclose(output);
   R_VERBOSE("Every data was written to file and output file closed successfully");
}




