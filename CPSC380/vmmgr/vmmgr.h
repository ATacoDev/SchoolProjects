#include <stdio.h> 
#include <stdlib.h> 

#define TLB_SIZE 16
#define PAGE_SIZE 256
#define FRAME_SIZE 256
#define NUM_FRAMES 256
#define BACKING_STORE_FILE "BACKING_STORE.bin"

int TLB[TLB_SIZE][2];
int TLBsize = 0;
        
int pageTable[256];
int memoryFull = 0;
int memory[NUM_FRAMES][FRAME_SIZE];

int numPageFaults = 0;
// counted during reading and used for calculations

void pageFault(int pageNum) {
    FILE *ptr = fopen(BACKING_STORE_FILE, "rb");

    if (ptr == NULL) {
        printf("Couldn't open the file\n"); 
        return;
    }

    if (fseek(ptr, PAGE_SIZE * pageNum, SEEK_SET) != 0) {
        printf("Page not found\n");
        return;
    }

    unsigned char buffer[FRAME_SIZE];
    fread(buffer, sizeof(buffer), 1, ptr);

    for (int i = 0; i < FRAME_SIZE; i++) {
        memory[memoryFull][i] = buffer[i];
    }

    pageTable[pageNum] = memoryFull;
    memoryFull++;

    printf("Page Fault Occurred for Page: %d\n", pageNum);
    numPageFaults++;
    printf("Number of Page Faults: %d\n", numPageFaults);

    fclose(ptr);
}

void updateTLB(int pageNum, int frameNum) {
    if (TLBsize != TLB_SIZE) {
        TLB[TLBsize][0] = pageNum;
        TLB[TLBsize][1] = frameNum;
        TLBsize++;
    } else {
        for (int i = 0; i < TLB_SIZE - 1; i++) {
            TLB[i][0] = TLB[i + 1][0];
            TLB[i][1] = TLB[i + 1][1];
        }
        TLB[TLB_SIZE - 1][0] = pageNum;
        TLB[TLB_SIZE - 1][1] = frameNum;
    }
}

void printAddressInfo(int logicalAddress, int pageNum, int offset, int frameNum) {
    int valueOfAdd = memory[frameNum][offset];
    int physicalAddress = frameNum * FRAME_SIZE + offset;
    printf("Virtual Address: %d, Physical Address: %d, Value: %d\n", 
    logicalAddress, physicalAddress, valueOfAdd);
}