#include "queue.h"

node_t pop_q(queue_t* queue) {
    if(queue->isEmpty == 1) {
        N_MAKE_INVALID(queue->queueCache[0]);
        return queue->queueCache[0];
    }
    
    if(queue->cacheBegin < queue->cacheEnd) {
        return queue->queueCache[queue->cacheBegin++];
    }
    queue->cacheBegin = 0;
    UCHAR check = fread(queue->queueCache, sizeof(node_t), QUEUE_CACHE_SIZE, queue->queueData);
    queue->cacheEnd = check;
    R_DEBUG("CACHE UPDATE: %d", check);
    
    if(check == 0) {
        queue->isEmpty = 1;
        N_MAKE_INVALID(queue->queueCache[0]);
        return queue->queueCache[0];
    }
    return queue->queueCache[0];
}

void push_q(queue_t* queue, node_t elem) {
    queue->isEmpty = 0;
    if(queue->cacheEnd < QUEUE_CACHE_SIZE) {
        queue->queueCache[queue->cacheEnd++] = elem;
        return;
    }
    long pos = ftell(queue->queueData);
    fwrite(&elem, sizeof(elem), 1, queue->queueData);
    fseek(queue->queueData, pos, SEEK_SET);
}

queue_t create_q() {
    queue_t queue;
    queue.isEmpty = 1;
    queue.queueCache = malloc(QUEUE_CACHE_SIZE * sizeof(node_t));
    queue.cacheBegin = 0;
    queue.cacheEnd = 0;
    queue.queueData = openFile(QUEUE_FILENAME, "w");
    fclose(queue.queueData);
    queue.queueData = openFile(QUEUE_FILENAME, "a+");
    return queue;
}

void delete_q(queue_t* queue) {
    fclose(queue->queueData);
    queue->isEmpty = 1;
    remove(QUEUE_FILENAME);
}