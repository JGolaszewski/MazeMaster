#include "queue.h"

node_t pop_q(queue_t* queue) {
    node_t data;
    if(queue->isEmpty == 1) {
        N_MAKE_INVALID(data);
        return data;
    }
    UCHAR check = fread(&data, sizeof(node_t), 1, queue->queueData);
    if(check == 0) {
        queue->isEmpty = 1;
        N_MAKE_INVALID(data);
        return data;
    }
    return data;
}

void push_q(queue_t* queue, node_t elem) {
    long pos = ftell(queue->queueData);
    queue->isEmpty = 0;
    fwrite(&elem, sizeof(elem), 1, queue->queueData);
    fseek(queue->queueData, pos, SEEK_SET);
}

queue_t create_q() {
    queue_t queue;
    queue.isEmpty = 1;
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