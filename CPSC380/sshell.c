#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80

int main(void) {
    char *args[MAX_LINE/2 + 1];
    int should_run = 1;
    pid_t pid;

    while (should_run == 1) {
        printf("osh>");
        fflush(stdout);

        char input[MAX_LINE];
        fgets(input, sizeof(input), stdin);

        int count = 0;
        char *token = strtok(input, " \n");
        while (token != NULL) {
            args[count] = token;
            token = strtok(NULL, " \n");
            count++;
        }
        args[count] = NULL;

        // check for '&' at end of command
        int backgroundProcess = 1;
        if (count > 0 && strcmp(args[count - 1], "&") == 0) { // if strcmp == 0, then args[count - 1] and '&' match
            backgroundProcess = 0;
            args[count - 1] = NULL; // if '&' exists, remove it as to not effect the command
        }
        pid = fork(); // fork child process

        if (pid == -1) { // fork fails
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // check if running
            
            execvp(args[0], args);

            perror("execvp");
            exit(EXIT_FAILURE);
        } else { // if no longer running, check if complete
           if (backgroundProcess == 1) {
                int status;
                waitpid(pid, &status, 0); // wait till process terminates
                if (WIFEXITED(status)) { // if process complete, then exit
                    printf("Child process exited with status %d\n", WEXITSTATUS(status));
                    should_run = 0;
                }
            }
        }
    }
    return 0;
}