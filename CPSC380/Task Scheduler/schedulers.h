#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

// add a task to the list 
void add(char *name, int priority, int burst);

// invoke the scheduler
void schedule_fcfs(struct task* taskList[]);
void schedule_priority(struct task* taskList[]);
void schedule_rr(struct task* taskList[]);
void schedule_sfj(struct task* taskList[]);
