#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "macros.h"

extern UCHAR verbose;
extern UCHAR debug;

#define R_ERROR(format, ...) {fprintf(stderr, "\x1b[31mERROR:\033[0m "); fprintf(stderr, format __VA_OPT__(, ) __VA_ARGS__); fprintf(stderr, "\n"); exit(EXIT_FAILURE);}
#define R_WARNING(format, ...) {fprintf(stderr, "\x1b[33mWARNING:\033[0m "); fprintf(stderr, format __VA_OPT__(, ) __VA_ARGS__); fprintf(stderr, "\n");}
#define R_INFO(format, ...) {fprintf(stderr, "\x1b[36mINFO:\033[0m "); fprintf(stderr, format __VA_OPT__(, ) __VA_ARGS__); fprintf(stderr, "\n");}

#define R_VERBOSE(format, ...) {if(verbose){fprintf(stderr, "VERBOSE: "); fprintf(stderr, format __VA_OPT__(, ) __VA_ARGS__); fprintf(stderr, "\n");}}
#define R_DEBUG(format, ...) {if(debug){fprintf(stderr, "\x1b[35mDEBUG:\033[0m "); fprintf(stderr, format __VA_OPT__(, ) __VA_ARGS__); fprintf(stderr, "\n");}}