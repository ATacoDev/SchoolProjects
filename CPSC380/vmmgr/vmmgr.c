#include "vmmgr.h"

int main(int argc, char *argv[]) { 

    // useful information when printing the statistics
        int logicalAddress;
        int pageFaultCount = 0;
        int TLBstat = 0;
        int totalAccesses = 0;

    if (argc == 2) {  // check correct number of argument
        char *fileName = argv[1];
        FILE *file = fopen(fileName, "r"); 
        
        if (file == NULL) { 
            printf("Couldn't open the file\n"); 
            return -1;
        } 

        for (int i = 0; i < 256; i++) {
            pageTable[i] = -1;
        }

        while (fscanf(file, "%d", &logicalAddress) != EOF) { 
            totalAccesses++;

            int pageNum = (logicalAddress >> 8) & 0xFF;
            int offset = logicalAddress & 0xFF;

            int TLBhit = 0;

            for (int i = 0; i < TLBsize; i++) {
                if (TLB[i][0] == pageNum) {
                    TLBhit = 1;
                    printAddressInfo(logicalAddress, pageNum, offset, TLB[i][1]);
                    TLBstat++;
                    break;
                }
            }

            if (TLBhit == 0) {
                if (pageTable[pageNum] == -1) {
                    pageFault(pageNum);
                    pageFaultCount++;
                }
                printAddressInfo(logicalAddress, pageNum, offset, pageTable[pageNum]);

                updateTLB(pageNum, pageTable[pageNum]);
            }
        }
        
        printf("\n\nPage-fault rate: %.2f %%\n", (1.0 * pageFaultCount) / (1.0 * totalAccesses) * 100.0);
        printf("TLB-hit rate: %.2f %%\n", (1.0 * TLBstat) / (1.0 * totalAccesses) * 100.0);
        
        fclose(file); 
    } else {
		printf("Usage: ./vmmgr [input file]\n");
	}
    return 0; 
}