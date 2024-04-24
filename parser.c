#include "parser.h"

USHORT mazeWidth = 0;

USHORT startX = USHRT_MAX;
USHORT startY = 0;

USHORT endX = USHRT_MAX;
USHORT endY = 0;

void readLineBit(FILE* in, char** outBuffer, USHORT* size) {
    char currentChar = '\0';
    *size = 0;
    *outBuffer = calloc(MAX_LINE_WIDTH/8 + 1, 1);

    //BUFFER MUST BE ALLOCATED
    if(!(*outBuffer)) R_ERROR("Couldnt allocate %d BYTES of memory!", MAX_LINE_WIDTH/8);

    //READ ONE LINE IN BITS
    while( (*size) <= MAX_LINE_WIDTH + 1 && !feof(in) && ((currentChar = fgetc(in)) != '\n')) {
        (*outBuffer)[(*size)/8] <<= ((*size)%8)? 0x1 : 0x0;
        if(currentChar == 'P') {
            startX = (*size);
            R_DEBUG("Poczatek w x: %d y: %d", startX, startY)
        } else if(currentChar == 'K') {
            endX = (*size);
            R_DEBUG("Koniec w x: %d y: %d", endX, endY)
        }
        (*outBuffer)[(*size)/8] |= (currentChar==WALL_CHAR)? 0x1 : 0x0;
        (*size)++;
    }
    (*size)--;
    

    //SHIFT ALL LOADED BITS TO LEFT IN LAST BYTE
    (*outBuffer)[(*size)/8] <<= 7 - (*size)%8;
    if(startX == USHRT_MAX) startY++;
    if(endX == USHRT_MAX) endY++;
}

void toGraph(FILE* tempF, const char* buffers[3], const USHORT lineSize, const USHORT height) { 
    node_t tempNode;
    tempNode.x = 0;
    tempNode.y = 0;
    tempNode.data.adj = 0;
    tempNode.data.flag = 0;
    tempNode.data.parent = 0;

    for(tempNode.x = 0; tempNode.x < lineSize; tempNode.x++) {
        //CHECK LEFT AND RIGHT ROAD
        if(tempNode.x != 0) {
            tempNode.data.adj |= (1 - GET_BIT(buffers[1], tempNode.x-1)) << 3;
        }

        if(tempNode.x < lineSize-1) {
            tempNode.data.adj |= (1 - GET_BIT(buffers[1], tempNode.x+1)) << 2;
        }

        //CHECK TOP AND BOTTOM ROAD
        tempNode.data.adj |= (1 - GET_BIT(buffers[0], tempNode.x)) << 1;
        tempNode.data.adj |= 1 - GET_BIT(buffers[2], tempNode.x);

        //STORE NODE IN TEMP FILE
        fwrite(&(tempNode.data), sizeof(nodeData_t), 1, tempF);

        tempNode.data.adj = 0;
    }
}

void parseFile(const char* filename) {
    FILE* in = NULL;
    FILE* nodeOut = NULL;
    in = openFile(filename, "r");
    nodeOut = openFile(TEMP_NODE_FILENAME, "w");

    char* buffers[3];

    node_t tempNode;
    tempNode.x = 0;
    tempNode.y = 0;
    tempNode.data.adj = 0;
    tempNode.data.flag = 0;
    tempNode.data.parent = 0;



    //HEIGHT OF BUFFERS IN FILE RELATIVE TO MIDDLE BUFFER 
    //(BUFFER[0] => height-1)
    //(BUFFER[1] => height)
    //(BUFFER[2] => height+1)
    USHORT height = 1;

    //READ 3 FIRST LINES
    readLineBit(in, &buffers[0], &mazeWidth);
    readLineBit(in, &buffers[1], &mazeWidth);
    readLineBit(in, &buffers[2], &mazeWidth);

    fwrite(&(tempNode.data), sizeof(nodeData_t), mazeWidth, nodeOut);

    while(!feof(in)) {
        //FIND INTERSECTIONS / TURN
        toGraph(nodeOut, buffers, mazeWidth, height);

        //SHIFT BUFFERS
        free(buffers[0]);
        buffers[0] = buffers[1];
        buffers[1] = buffers[2];

        //READ NEXT LINE
        readLineBit(in, &buffers[2], &mazeWidth);
        height++;
    }
    toGraph(nodeOut, buffers, mazeWidth, height);

    //FREE BUFFERS MEM
    free(buffers[0]);
    free(buffers[1]);
    free(buffers[2]);
    
    fclose(in);
    fclose(nodeOut);
}
