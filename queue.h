#pragma once

#include <assert.h>
#include <unistd.h>

#include "graph.h"
#include "interface.h"
#include "macros.h"
#include "reports.h"

typedef struct Queue {
    FILE* queueData;
    UCHAR isEmpty : 1;
} queue_t;

#define Q_ISEMPTY(queue) feof((queue)->queueData)

queue_t create_q();
void delete_q(queue_t* queue);

node_t pop_q(queue_t* queue);
void push_q(queue_t* queue, node_t elem);