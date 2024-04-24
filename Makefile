CC := cc
OUTFILENAME := bin.exe
OUTDIR := ./bin
PROGRAMDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
MACROS := -DPROGRAM_DIR="\"$(PROGRAMDIR)\""
CFLAGS := -std=c2x -pedantic -Wall
CFILES := main.c parser.c interface.c graph.c BFS.c queue.c readPath.c

all: build

build:
	$(CC) $(MACROS) $(CFLAGS) -o "$(OUTDIR)/$(OUTFILENAME)" $(CFILES)

clean:
	rm -rf "$(OUTDIR)/$(OUTFILENAME)"

test:
	./bin/bin.exe -i maze.txt -v -d

.PHONY: all build clean test install