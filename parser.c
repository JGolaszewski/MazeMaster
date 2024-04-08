#include "parser.h"

void readLineBit(FILE* in, char** outBuffer, USHORT* size) {
    char currentChar = '\0';
    *size = 0;
    *outBuffer = calloc(MAX_LINE_WIDTH/8, 1);

    //BUFFER MUST BE ALLOCATED
    if(!(*outBuffer)) R_ERROR("Couldnt allocate %d BYTES of memory!", MAX_LINE_WIDTH/8);

    //READ ONE LINE IN BITS
    while( (*size) < MAX_LINE_WIDTH && !feof(in) && ((currentChar = fgetc(in)) != '\n')) {
        (*outBuffer)[(*size)/8] <<= ((*size)%8)? 0x1 : 0x0;
        (*outBuffer)[(*size)/8] |= (currentChar==WALL_CHAR)? 0x1 : 0x0;

        (*size)++;
    }

    //SHIFT ALL LOADED BITS TO LEFT IN LAST BYTE
    (*outBuffer)[(*size)/8] <<= 8 - (*size)%8;
    
    //REALLOC MEM BUFFER TO FIT
    if((*size) < MAX_LINE_WIDTH) {
        char* temp = realloc((*outBuffer), (*size)/8 + (((*size)%8 != 0)? 1 : 0));
        if(temp) (*outBuffer) = temp;
    }    
}

void toGraph(FILE* tempF, const char* buffers[3], const USHORT lineSize, const USHORT height) {    
    node_t tempNode;
    tempNode.y = height;
    tempNode.flag = 0;

    for(tempNode.x = 0; tempNode.x < lineSize; tempNode.x++) {
        if(GET_BIT(buffers[1], tempNode.x) == 1) continue;
        //CHECK LEFT AND RIGHT ROAD
        if(tempNode.x != 0) {
            tempNode.adj |= (1 - GET_BIT(buffers[1], tempNode.x-1)) << 3;
        }

        if(tempNode.x < lineSize-1) {
            tempNode.adj |= (1 - GET_BIT(buffers[1], tempNode.x+1)) << 2;
        }

        //CHECK TOP AND BOTTOM ROAD
        tempNode.adj |= (1 - GET_BIT(buffers[0], tempNode.x)) << 1;
        tempNode.adj |= 1 - GET_BIT(buffers[2], tempNode.x);

        //STORE NODE IN TEMP FILE
        fwrite(&tempNode, sizeof(tempNode), 1, tempF);

        tempNode.adj = 0;
    }
}

void parseFile(const char* filename) {
    FILE* in = NULL;
    FILE* nodeOut = NULL;
    in = openFile(filename, "r");
    nodeOut = openFile(TEMP_NODE_FILENAME, "w");

    char* buffers[3];
    USHORT lineSize = 0;

    //HEIGHT OF BUFFERS IN FILE RELATIVE TO MIDDLE BUFFER 
    //(BUFFER[0] => height-1)
    //(BUFFER[1] => height)
    //(BUFFER[2] => height+1)
    USHORT height = 1;

    //TODO: CHECK IF FILE IS BINARY IF IT IS READ LINE W FREAD INSTEAD OF READLINEBIT

    //READ 3 FIRST LINES
    readLineBit(in, &buffers[0], &lineSize);
    readLineBit(in, &buffers[1], &lineSize);
    readLineBit(in, &buffers[2], &lineSize);

    while(!feof(in)) {
        //FIND INTERSECTIONS / TURN
        toGraph(nodeOut, buffers, lineSize, height);

        //SHIFT BUFFERS
        free(buffers[0]);
        buffers[0] = buffers[1];
        buffers[1] = buffers[2];

        //READ NEXT LINE
        readLineBit(in, &buffers[2], &lineSize);
        height++;
    }

    //FREE BUFFERS MEM
    free(buffers[0]);
    free(buffers[1]);
    free(buffers[2]);
    
    fclose(in);
    fclose(nodeOut);
}
