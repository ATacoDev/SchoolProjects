#include "buffer.h"

buffer_item buffer[BUFFER_SIZE];
int front = 0; // remove
int rear = 0;  // insert

int insert_item(buffer_item item) {
    if ((rear + 1) % BUFFER_SIZE == front) {
        return -1;
    }

    buffer[rear] = item;
    rear = (rear + 1) % BUFFER_SIZE;
    return 0; // Successful insert
}

int remove_item(buffer_item *item) {
    if (front == rear) {
        return -1;
    }

    *item = buffer[front];
    front = (front + 1) % BUFFER_SIZE;
    return 0; // Successful removal
}
