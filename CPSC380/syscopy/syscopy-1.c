#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 
#include <errno.h>
#include <sys/syscall.h>

int main(int argc, char *argv[])
{
	char buf;
	int inputFile, outputFile;

	if (argc != 3) {
		fprintf(stderr, "Invalid number of arguments. Error code: %d\n", errno); // # of arguments isn't 2
	} else {
		inputFile = syscall(SYS_open, argv[1], O_RDONLY);
		outputFile = syscall(SYS_open, argv[2], O_RDONLY);

	if (inputFile == -1)
	{
		fprintf(stderr, "Error opening inputFile. Error code: %d\n", errno); // input file doesn't exist or is input incorrectly
		close(inputFile);
		return 0;
	}

	if (outputFile != -1) {
		printf("Output file already exists! Please specify new name\n"); // output already exists

		return 0;
	}

	outputFile = syscall(SYS_open, argv[2],  O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 
	
	while(syscall(SYS_read, inputFile, &buf, 1))
	{
		syscall(SYS_write, outputFile, &buf, 1);
	}

	syscall(SYS_write, 1, "Copy Completed!\n", 16);

	syscall(SYS_close, inputFile);
	syscall(SYS_close, outputFile);
	return 0;
	}
}
