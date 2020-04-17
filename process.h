#include <sleep_list.h>

// Process' states

#define CREATED             0   // Process when just got created
#define READY_TO_RUN        1   // Ready to be scheduled
#define KERNEL_RUNNING      2   // Running on kernel space
#define USER_RUNNING        3   // Running on user space
#define PREMPTED            4   // Stopped by an interruption
#define ASLEEP              5   //  
#define ZOMBIE              6   // Process that was exited
#define TERMINATED          7   // Process ended normally    

// Define if the process is interrumtable by software
#define PROCESS_UNINTERRUPTIBLE 0
#define PROCESS_INTERRUPTIBLE   1


// Interrupts identifiers
#define ITR_IO_COMP          0
#define ITR_WAIT_BUFF        1
#define ITR_WAIT_TTY_INPUT   2


typedef struct{

} Signals;

typedef struct{
    
} Process_timer;

typedef struct{
    int state;                  // Process state
    int dir;                    // Direction in memory of the process
    char *kstack;               // Bottom of kernel stack for this process
    int uid;                    // User id
    int pid;                    // Process id
    Proc * parent;              // Parent process
    int nice;                   // Scheduling parameters
    int is_interrumptable;      // 1 interrumptable, 0 not interrumptable
    Signals *signals;           // List of signals received but not processed
    Process_timer timers;       // Accounting
} Proc;

typedef Proc  **Process_table;  // Table that contains all processes

/*  SLEEP
    Set the process to sleep mode, also adds it to a list that contains all processes in that state by the same interruption.
    PARAMETERS:
        int itr         : Identifier of the interruption
        Proc * proc     : Pointer to the process you want to sleep
        int priority    : Priority of the process

        
        * The priority it may get removed since we have a similar field in Proc (nice field) which can do the same job.

    RETURNS:
        int             : Returns 0 if the process has been slept sucessfully, otherwise sends 1.
*/

int sleep ( int itr, Proc * proc , int priority );

/*  WAKE_UP
    Removes the process from the asleep process list and changes it to be ready to run or awaken
    PARAMETERS:
        Proc * proc     : Pointer to the process you want to awaken

    RETURNS:
        void            : There is no return value
*/

void wake_up (Proc *proc);