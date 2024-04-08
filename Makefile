CC := cc

OUTFILENAME := bin.exe
OUTDIR := ./bin

PROGRAMDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
MACROS := -DPROGRAM_DIR="\"$(PROGRAMDIR)"\"
CFLAGS := -std=c2x -pedantic -Wall

CFILES := main.c parser.c interface.c graph.c BFS.c

all:
	$(CC) $(MACROS) $(CFLAGS) -o "$(OUTDIR)/$(OUTFILENAME)" $(CFILES)
