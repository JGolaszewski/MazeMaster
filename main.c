#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "graph.h"
#include "parser.h"
#include "interface.h"
#include "reports.h"

UCHAR verbose = 0;
UCHAR debug = 0;

int main(int argc, char** argv) {
    #ifndef PROGRAM_DIR
        R_ERROR("Program directory not defined! Recompile program with given Makefile!");
    #endif
    
    char *input_file = NULL;
    char *output_file = NULL;

    parse_args(argc, argv, &input_file, &output_file);

    chdir(PROGRAM_DIR);
    R_DEBUG("Working dir: %s", PROGRAM_DIR);

    if(input_file == NULL) R_ERROR("Input file not specified!");
    if(input_file == output_file) R_ERROR("Input file is the same as output file");

    R_VERBOSE("Input file: %s", input_file);
    R_VERBOSE("Output file: %s", (output_file==NULL)? "Not specified": output_file);

    R_VERBOSE("Parsing to graph...");
    
    parseFile(input_file);
    FILE* nodes = openFile(TEMP_NODE_FILENAME, "r");
    node_t n = getNode(nodes, 1, 2);
    R_DEBUG("Node: x = %d, y = %d, adj = %d", n.x, n.y, n.adj);
    return 0;
}
