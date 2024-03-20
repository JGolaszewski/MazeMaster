#include "parser.h"

void readLineBit(FILE* in, char** outBuffer, USHORT* size) {
    char currentChar = '\0';
    *size = 0;
    *outBuffer = calloc(MAX_LINE_WIDTH/8, 1);

    //BUFFER MUST BE ALLOCATED
    if(!(*outBuffer)) return;

    //READ ONE LINE IN BITS
    while( (*size) < MAX_LINE_WIDTH && !feof(in) && ((currentChar = fgetc(in)) != '\n')) {
        //printf("CURRENT CHAR: %c\n", currentChar);
        
        (*outBuffer)[(*size)/8] <<= ((*size)%8)? 0x1 : 0x0;
        (*outBuffer)[(*size)/8] |= (currentChar==WALL_CHAR)? 0x1 : 0x0;

        //printf("CURRENT BUFFER[%d]: ", (*size)/8);
        //printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((*outBuffer)[(*size)/8]));
        //printf("\n\n");

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

void toGraph(FILE* out, FILE* adjMatrix, const char* buffers[3], const USHORT lineSize, const USHORT height) {
    //TODO: Add horizontal connections to adjacency matrix
    
    //BITS: 0b(PREV LEFT)(PREV RIGHT)(PREV TOP)(PREV BOTTOM)(LEFT)(RIGHT)(TOP)(BOTTOM)    
    UCHAR roadData = 0;
    static UINT id = 0;
    UINT nodeId = 0;
    for(USHORT i = 0; i < lineSize; i++) {

        //CHECK LEFT AND RIGHT ROAD
        if(i != 0) {
            roadData |= (1 - GET_BIT(buffers[1], i-1)) << 3;
        }

        if(i < lineSize-1) {
            roadData |= (1 - GET_BIT(buffers[1], i+1)) << 2;
        }

        //CHECK TOP AND BOTTOM ROAD
        roadData |= (1 - GET_BIT(buffers[0], i)) << 1;
        roadData |= 1 - GET_BIT(buffers[2], i);

        //STORE NODE (INTERSECTION / TURN) IN TEMP FILE
        if((roadData&0b1100) > 0 && (roadData&0b11) > 0) {
            fprintf(out, TEMP_NODE_FORMAT(id++, i, height, roadData&0b1111));
            
            if((roadData & 0b01000000) > 0 && (roadData & 0b00001000) > 0) {
                fprintf(adjMatrix, "%d %d\n%d %d\n",id-2, id-1, id-1, id-2);
            }

            //SHIFT INTERSECTION TO PREV INTERSECTION
            roadData <<= 4;
        }

    roadData &= 0b11110000;
    }
}

void parseFile(const char* filename) {
    FILE* in = NULL;
    FILE* nodeFile = NULL;
    FILE* matrixFile = NULL;
    fopen_s(&in, filename, "r");
    fopen_s(&nodeFile, TEMP_NODE_FILENAME, "w");
    fopen_s(&matrixFile, TEMP_MATRIX_FILENAME, "w");

    char* buffers[3];
    USHORT lineSize = 0;

    //HEIGHT OF BUFFERS IN FILE RELATIVE TO MIDDLE BUFFER 
    //(BUFFER[0] => height-1)
    //(BUFFER[1] => height)
    //(BUFFER[2] => height+1)
    USHORT height = 1;
    
    //READ 3 FIRST LINES
    readLineBit(in, &buffers[0], &lineSize);
    readLineBit(in, &buffers[1], &lineSize);
    readLineBit(in, &buffers[2], &lineSize);

    while(!feof(in)) {
        //FIND INTERSECTIONS / TURN
        toGraph(nodeFile, matrixFile, buffers, lineSize, height);

        //SHIFT BUFFERS
        free(buffers[0]);
        buffers[0] = buffers[1];
        buffers[1] = buffers[2];

        //READ NEXT LINE
        readLineBit(in, &buffers[2], &lineSize);
        height++;
    }

    //TODO: Add vertical connections to adjacency matrix
    //TODO: (Optional) smooth the graph by removing turns 

    //FREE BUFFERS MEM
    free(buffers[0]);
    free(buffers[1]);
    free(buffers[2]);
}