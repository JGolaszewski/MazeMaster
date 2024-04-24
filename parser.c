#include "parser.h"

UCHAR isBinary = 0;
fileHeader_h fileData;

USHORT startX = USHRT_MAX;
USHORT startY = 0;

USHORT endX = USHRT_MAX;
USHORT endY = 0;

void readLineBit(FILE* in, char** outBuffer) {
    USHORT pos = 0;
    char currentChar = '\0';
    pos = 0;
    *outBuffer = calloc(fileData.columns/8 + 1, 1);

    //BUFFER MUST BE ALLOCATED
    if(!(*outBuffer)) R_ERROR("Couldnt allocate %d BYTES of memory!", fileData.columns/8 + 1);

    //READ ONE LINE IN BITS
    while(((currentChar = fgetc(in)) != '\n') && !feof(in)) {
        if(currentChar == START_CHAR) {
            fileData.startX = pos;
            R_VERBOSE("Found start tile in position x: %d y: %d", fileData.startX, fileData.startY)
        } else if(currentChar == END_CHAR) {
            fileData.endX = (pos);
            R_VERBOSE("Found finish tile in position x: %d y: %d", fileData.endX, fileData.endY)
        }

        switch(currentChar) {
            case START_CHAR:
            case END_CHAR:
            case PATH_CHAR:
                (*outBuffer)[(pos)/8] <<= ((pos)%8)? 0x1 : 0x0;
                (*outBuffer)[(pos)/8] |= 0b0;
                (pos)++;
                break;
            case WALL_CHAR:
                (*outBuffer)[(pos)/8] <<= ((pos)%8)? 0x1 : 0x0;
                (*outBuffer)[(pos)/8] |= 0b1;
                (pos)++;
                break;
            case EOF:
            case '\r':
                continue;
            default:
                R_ERROR(" (PARSER) Unknown char in file with code: %d ", currentChar);
        }
    }
    pos--;
    //SHIFT ALL LOADED BITS TO LEFT IN LAST BYTE
    (*outBuffer)[pos/8] <<= 7 - pos%8;

    if(fileData.startX == USHRT_MAX) fileData.startY++;
    if(fileData.endX == USHRT_MAX) fileData.endY++;
}

void binReadLineBit(FILE* in, char** outBuffer) {
    
}

void toGraph(FILE* tempF, char* buffers[3], const USHORT height) {
    nodeData_t* bufferOut = calloc(fileData.columns, sizeof(nodeData_t));
    for(USHORT i = 0; i <= fileData.columns; i++) {
        //CHECK LEFT AND RIGHT ROAD
        if(i != 0) {
            bufferOut[i].adj |= (1 - GET_BIT(buffers[1], i-1)) << 3;
        }

        if(i < fileData.columns-1) {
            bufferOut[i].adj |= (1 - GET_BIT(buffers[1], i+1)) << 2;
        }

        //CHECK TOP AND BOTTOM ROAD
        bufferOut[i].adj |= (1 - GET_BIT(buffers[0], i)) << 1;
        bufferOut[i].adj |= 1 - GET_BIT(buffers[2], i);
    }
    fwrite(bufferOut, sizeof(nodeData_t), fileData.columns, tempF);
}

USHORT preParser(FILE* file) {
    R_DEBUG("Pre parser start...");
    int fileSignature = -1;
    char escKey = -1;
    fread(&fileSignature, sizeof(int), 1, file);
    fread(&escKey, sizeof(char), 1, file);
    if(fileSignature == FILE_SIGNATURE && escKey == ESCAPE_CODE) {
        isBinary = 1;
        fread(&fileData, sizeof(fileHeader_h), 1, file);

        R_WARNING("Detected binary input file, output file will be ignored if provided");
        fileData.columns = fileData.columns * 2 - 1;
        fileData.lines = fileData.lines * 2 - 1;
        fileData.startX--;
        fileData.startY--;
        fileData.endX = (fileData.endX - 1) * 2;
        fileData.endY = (fileData.endY - 1 ) * 2 + 1;
        R_DEBUG("Size: %d %d  Start: %d %d  End: %d %d  Wall: %c  Path: %c", fileData.columns, fileData.lines, fileData.startX, fileData.startY, fileData.endX, fileData.endY, fileData.wall, fileData.path);
        R_DEBUG("Pre parser end...");
        return 0;
    }

    memset(&fileData, 0, sizeof(fileHeader_h));
    fileData.startX = USHRT_MAX;
    fileData.startY = 0;
    fileData.endX = USHRT_MAX;
    fileData.endY = 0;
    rewind(file);

    char curChar = '\0';
    char prevChar = '\0';
    int prevLineS = -1;
    int curLineS = 0;
    USHORT lineCount = 0;
    USHORT errCount = 0;
    while((curChar = getc(file)) != EOF) {
        if(curChar == '\r') continue;
        if(curChar == '\n') {
            //Check if line ends with wall or exit/start
            if(prevChar != '\0' && prevChar != WALL_CHAR && prevChar != START_CHAR && prevChar != END_CHAR) {
                R_WARNING(" (PRE PARSER) Line %d in input file doesnt end with valid char", lineCount);
                errCount++;
            }

            if(prevLineS != -1 && (curLineS != prevLineS)) {
                R_WARNING(" (PRE PARSER) Line %d and line %d in input file have diffrent lengths (size1: %d, size2: %d)", lineCount - 1, lineCount, prevLineS, curLineS);
                errCount++;
            }

            lineCount++;
            prevLineS = curLineS;
            curLineS = 0;
        } else {
            curLineS++;
            switch(curChar) {
                case WALL_CHAR:
                case PATH_CHAR:
                case START_CHAR:
                case END_CHAR:
                case EOF:
                    break;
                default:
                    R_WARNING(" (PRE PARSER) Unknown char with code: %d found in line %d", curChar, lineCount);
                    errCount++;
            }
        }
        prevChar = '\0';
    }
    
    if(prevLineS != -1 && (curLineS != prevLineS)) {
        R_WARNING(" (PRE PARSER) Line %d and line %d in input file have diffrent lengths (size1: %d, size2: %d)", lineCount - 1, lineCount, prevLineS, curLineS);
        errCount++;
    }

    rewind(file);
    fileData.columns = prevLineS;

    R_DEBUG("Pre parser end...");
    return errCount;
}

void parseFile(const char* filename) {
    FILE* in = NULL;
    FILE* nodeOut = NULL;
    in = openFile(filename, "r");
    nodeOut = openFile(TEMP_NODE_FILENAME, "w");

    USHORT err = preParser(in);
    if(err > 0) R_ERROR("Pre parser found %d errors in input file, please provide correct input file!", err);

    char* buffers[3];

    //HEIGHT OF BUFFERS IN FILE RELATIVE TO MIDDLE BUFFER 
    //(BUFFER[0] => height-1)
    //(BUFFER[1] => height)
    //(BUFFER[2] => height+1)
    USHORT height = 1;

    //READ 3 FIRST LINES
    if(isBinary) {
        binReadLineBit(in, &buffers[0]);
        return;
        binReadLineBit(in, &buffers[1]);
        binReadLineBit(in, &buffers[2]);
    } else {
        readLineBit(in, &buffers[0]);
        readLineBit(in, &buffers[1]);
        readLineBit(in, &buffers[2]);
    }

    while(!feof(in)) {
        //FIND INTERSECTIONS / TURN
        toGraph(nodeOut, buffers, height);

        //SHIFT BUFFERS
        free(buffers[0]);
        buffers[0] = buffers[1];
        buffers[1] = buffers[2];

        //READ NEXT LINE
        readLineBit(in, &buffers[2]);
        height++;
    }
    toGraph(nodeOut, buffers, height);

    //FREE BUFFERS MEM
    free(buffers[0]);
    free(buffers[1]);
    free(buffers[2]);
    
    fclose(in);
    fclose(nodeOut);
}
