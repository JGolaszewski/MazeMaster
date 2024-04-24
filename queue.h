#pragma once

#include <assert.h>
#include <unistd.h>

#include "graph.h"
#include "interface.h"
#include "macros.h"
#include "reports.h"

#define QUEUE_CACHE_SIZE 1000

typedef struct Queue {
    FILE* queueData;
    node_t* queueCache;
    UCHAR isEmpty : 1;
    USHORT cacheBegin;
    USHORT cacheEnd;
} queue_t;

#define Q_ISEMPTY(queue) feof((queue)->queueData)

queue_t create_q();
void delete_q(queue_t* queue);

node_t pop_q(queue_t* queue);
void push_q(queue_t* queue, node_t elem);