#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <errno.h>

double random_double() { // returns a random double in [0,1)
    return random() / ((double)RAND_MAX + 1);
}

void* countPoints(void* arg) { //  each individual thread will call to count the number of points that fall within the circle
    int* hitCountPtr = (int*)arg;
    int localHitCount = 0; //  local count per thread
    int pointsPerThread = *hitCountPtr;

    for (int i = 0; i < pointsPerThread; i++) {  //  fully random points
        double x = random_double() * 2.0 - 1.0;
        double y = random_double() * 2.0 - 1.0;
        if (sqrt(x * x + y * y) < 1.0) {
            localHitCount++;
        }
    }
    *hitCountPtr = localHitCount;
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

    if (argc != 2) { //  error handling
		fprintf(stderr, "Invalid number of arguments. Error code: %d\n", errno); // # of arguments isn't 2
	} else if (atoi(argv[1]) <= 0) {
        fprintf(stderr, "Points must be an integer greater than 0. Error code: %d\n", errno); // # of points is less than or equal to 0
    } else {

        int numThreads = 4; //  total number of threads

        pthread_t threads[numThreads];
        int numPoints = atoi(argv[1]);
        int individualThreadPoints[numThreads];
        int totalHitCount = 0;

        srand(time(NULL));

        for (int i = 0; i < numThreads; i++) {
            individualThreadPoints[i] = numPoints / numThreads;
            if (pthread_create(&threads[i], NULL, countPoints, &individualThreadPoints[i]) != 0) { // create the thread and have it execute countPoints()
                perror("pthread_create() error"); //  exit if return value is not 0
            }
        }

        for (int i = 0; i < numThreads; i++) {  //  exit if there was an error creating or joining the threads
            if (pthread_join(threads[i], NULL) != 0) {
                perror("pthread_join() error");
                exit(EXIT_FAILURE);
            }

            totalHitCount += individualThreadPoints[i];
        }

        double piEstimate = 4.0 * totalHitCount / numPoints; //  calcculate pi estimate
        printf("Estimate pi value: %f\n", piEstimate);

    }
    return 0;
}
