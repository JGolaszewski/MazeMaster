#include <stdio.h>
#include <stdlib.h>

size_t countLines(FILE* f) {
    size_t count = 0;
    char line [1024];
    while(fgets(&line, 1024, f)) count++;
    rewind(f);
    return count;
}

int main(int argc, char** argv) {
    FILE* f = fopen("../in/maze.txt", "r");
    if(!f) return -1;

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    size_t chunkSize = size / 16;

    rewind(f);

    char* chunk = malloc(sizeof(char) * chunkSize);
    if(!chunk) return -1;
    char ch = ' ';
    size_t s = countLines(f);

    printf("%d %d", (int)s, (int)((size-s)/s));
    return 0;
}