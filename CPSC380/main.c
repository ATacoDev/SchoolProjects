#include "buffer.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int sleepTime;

buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t buffer_mutex;
pthread_cond_t buffer_not_full, buffer_not_empty;
bool terminate = false;

void *producer(void *param) {
    buffer_item item;
    while (!terminate) {
        for (int i = 0; i < 30; i++) {
            item.data[i] = (uint8_t)(rand() % 256); 
        }

        item.cksum = 0; 
        for (int i = 0; i < 30; i++) {
            item.cksum ^= item.data[i]; // Calculate checksum using ^= bitwise operator
        }

        pthread_mutex_lock(&buffer_mutex);

        // wait for buffer to clear
        while (insert_item(item) == -1 && !terminate) {
            pthread_cond_wait(&buffer_not_full, &buffer_mutex);
        }

        if (!terminate) {
            printf("Producer produced data.");
            // for (int i = 0; i < 30; i++) {
            //     printf("%d ", item.data[i]);
            // }
            printf(" Checksum: %d\n", item.cksum);

            // Signal that the buffer is not empty
            pthread_cond_signal(&buffer_not_empty);
        }

        pthread_mutex_unlock(&buffer_mutex);
        sleep(sleepTime);
    }
    return NULL;
}

void *consumer(void *param) {
    buffer_item item;
    while (!terminate) {
        pthread_mutex_lock(&buffer_mutex);

        while (remove_item(&item) == -1 && !terminate) {

            pthread_cond_wait(&buffer_not_empty, &buffer_mutex);
        }

        if (!terminate) {
            printf("Consumer consumed data.");
            // for (int i = 0; i < 30; i++) {
            //     printf("%d ", item.data[i]);
            // }
            printf(" Checksum: %d\n", item.cksum);

            pthread_cond_signal(&buffer_not_full);
        }

        pthread_mutex_unlock(&buffer_mutex);
        sleep(sleepTime);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if (argc != 4) {
        fprintf(stderr, "Usage: ./prodcon <sleepTime> <producerThreads> <consumerThreads>\n");
        return -1;
    }

    sleepTime = atoi(argv[1]);
    int producerThreads = atoi(argv[2]);
    int consumerThreads = atoi(argv[3]);

    printf("sleepTime: %d\n", sleepTime);
    printf("producerThreads: %d\n", producerThreads);
    printf("consumerThreads: %d\n", consumerThreads);

    pthread_mutex_init(&buffer_mutex, NULL);
    pthread_cond_init(&buffer_not_full, NULL);
    pthread_cond_init(&buffer_not_empty, NULL);

    // Create producer threads
    pthread_t producer_threads[producerThreads];
    for (int i = 0; i < producerThreads; i++) {
        if (pthread_create(&producer_threads[i], NULL, producer, NULL) != 0) {
            fprintf(stderr, "Error: Failed to create producer thread %d\n", i);
            return -1;
        }
    }

    // Create consumer threads
    pthread_t consumer_threads[consumerThreads];
    for (int i = 0; i < consumerThreads; i++) {
        if (pthread_create(&consumer_threads[i], NULL, consumer, NULL) != 0) {
            fprintf(stderr, "Error: Failed to create consumer thread %d\n", i);
            return -1;
        }
    }


    sleep(sleepTime);

    // Set terminate flag
    pthread_mutex_lock(&buffer_mutex);
    terminate = true;
    pthread_mutex_unlock(&buffer_mutex);

    // Signal threads to wake up and exit
    for (int i = 0; i < producerThreads; i++) {
        pthread_cond_signal(&buffer_not_full);
    }

    for (int i = 0; i < consumerThreads; i++) {
        pthread_cond_signal(&buffer_not_empty);
    }

    for (int i = 0; i < producerThreads; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    for (int i = 0; i < consumerThreads; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    pthread_mutex_destroy(&buffer_mutex);
    pthread_cond_destroy(&buffer_not_full);
    pthread_cond_destroy(&buffer_not_empty);

    return 0;
}
