#pragma once

#include <stdio.h>
#include <stdlib.h>

#define REPORT_ERROR(msg) fprintf(stderr, "ERROR: %s\n", msg)
#define REPORT_WARNING(msg) fprintf(stderr, "WARNING: %s\n", msg)
#define REPORT_INFO(msg) fprintf(stdout, "INFO: %s\n", msg)

void report_error_exit(const char *msg) {
    fprintf(stderr, "ERROR: %s\n", msg);
    exit(EXIT_FAILURE);
}