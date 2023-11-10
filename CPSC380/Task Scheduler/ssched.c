#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "cpu.h"

#define SIZE    100

int count = 0;

void schedule_fcfs(struct task* taskList[]) {
   for (int i = 0; i < count; i++)
   {
      run(taskList[i], taskList[i]->burst);
      // printf("Running task = [%s] [%d] [%d] for %d units.\n",taskList[i]->name, taskList[i]->priority, taskList[i]->burst, taskList[i]->burst);
   }
}

void schedule_priority(struct task* taskList[]) {
   // Sort the taskList array based on priority
   for (int i = 0; i < count; i++) {
      for (int j = i + 1; j < count; j++) {
         if (taskList[i]->priority < taskList[j]->priority) {
            struct task* temp = taskList[i];
            taskList[i] = taskList[j];
            taskList[j] = temp;
         }
      }
   }

   for (int i = 0; i < count; i++)
   {
      run(taskList[i], taskList[i]->burst);
      // printf("Running task = [%s] [%d] [%d] for %d units.\n",taskList[i]->name, taskList[i]->priority, taskList[i]->burst, taskList[i]->burst);
   }
   
}

void schedule_rr(struct task* taskList[]) {
   int remainingBurst[count]; // Array to store remaining burst time for each task
   int timeQuantum = 2;
    int currentTime = 0; // Tracks the current time

    // Initialize remainingBurst for each task
    for (int i = 0; i < count; i++) {
        remainingBurst[i] = taskList[i]->burst;
    }

    // Keep scheduling until all tasks are done
    while (1) {
      printf("Starting from top of queue...\n");
        int done = 1; // Flag to check if all tasks are done

        for (int i = 0; i < count; i++) {
            if (remainingBurst[i] > 0) {
                done = 0; // At least one task is not done

                // Execute the task for a time quantum or until it finishes
                if (remainingBurst[i] > timeQuantum) {
                    currentTime += timeQuantum;
                    remainingBurst[i] -= timeQuantum;
                  run(taskList[i], timeQuantum);
                    printf("Units left: %d\n", remainingBurst[i]);
                    printf("\n");
                } else {
                    currentTime += remainingBurst[i];
                    remainingBurst[i] = 0;
                    run(taskList[i], timeQuantum);
                    printf("Units left: %d\n", remainingBurst[i]); 
                    printf("\n");
                }
            }
        }

        if (done) {
            break; // All tasks are done
        } 
    }
}

void schedule_sfj(struct task* taskList[]) {
   // Sort the taskList array based on burst time
   for (int i = 0; i < count; i++) {
      for (int j = i + 1; j < count; j++) {
         if (taskList[i]->burst > taskList[j]->burst) {
            struct task* temp = taskList[i];
            taskList[i] = taskList[j];
            taskList[j] = temp;
         }
      }
   }

   for (int i = 0; i < count; i++)
   {
      run(taskList[i], taskList[i]->burst);
      // printf("Running task = [%s] [%d] [%d] for %d units.\n",taskList[i]->name, taskList[i]->priority, taskList[i]->burst, taskList[i]->burst);
   }
}

void add(char *name, int priority, int burst) {
    printf("Add: %s, %d, %d\n", name, priority, burst);
}

int main(int argc, char *argv[])
{
    FILE *in;
    char *temp;
    char task[SIZE];

    struct task* taskList[SIZE];

    char *name;
    int   priority;
    int   burst;
    int   index = 0;

    if (argc != 3) {
        printf("Usage: %s <sched> <taskList> \n", argv[0]);
        return -1;
    }

    in = fopen(argv[2],"r");
    
    while (fgets(task,SIZE,in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp,",");
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));

        // ceate the task add the task to the scheduler's list of tasks
         // add(name, priority, burst);
         
         // Create the task
       struct task* newTask = (struct task*)malloc(sizeof(struct task));
      if (newTask != NULL) {
          newTask->name = strdup(name);
          newTask->priority = priority;
          newTask->burst = burst;

          // Store the task pointer in the taskList array
          taskList[count] = newTask;
          count++;
    } else {
        printf("Error: Memory allocation for task failed\n");
    }
        free(temp);
    }

    fclose(in);

    // invoke the scheduler
    if (strncmp(argv[1], "fcfs", 4) == 0) {
       schedule_fcfs(taskList);
    } else if (strncmp(argv[1], "priority", 8) == 0) {
       schedule_priority(taskList);
    } else if (strncmp(argv[1], "rr", 2) == 0) {
       schedule_rr(taskList);
    } else if (strncmp(argv[1], "sjf", 3) == 0) {
       schedule_sfj(taskList);
    } else {
       printf("Error: scheduler '%s' not supported \n", argv[1]);
       return -1;
    }

    return 0;
}

// include in README file: That time quantum is manually set to 2
