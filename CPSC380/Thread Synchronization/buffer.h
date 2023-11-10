#include <stdint.h>

// Define the buffer item structure
typedef struct buffer_item {
    uint8_t data[30];
    uint16_t cksum;
} buffer_item;

// Define the buffer size constant
#define BUFFER_SIZE 10

// Function declarations
int insert_item(buffer_item item);
int remove_item(buffer_item *item);

