
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
    Context * u_context;        // Context of the process in user mode
    Context * k_context;        // Context of the process in kernel mode
    int awake;                  // 0 awake 1 sleep
    int nice;                   // Scheduling parameters
    Signals *signals;           // List of signals received but not processed
    Process_timer timers;       // Accounting
} Proc;

typedef Proc  *Process_table;   // Table that contains all processes

/*  SLEEP
    Set the process to sleep mode, also adds it to a list that contains all processes in that state.
    PARAMETERS:
        Proc * proc     : Pointer to the process you want to sleep
        int priority    : Priority of the process 
        
        * The priority it may get removed since we have a similar field in Proc (nice field) which can do the same job.

    RETURNS:
        int             : Returns 0 if the process has been slept sucessfully, otherwise sends 1.
*/

int sleep (  Proc * proc , int priority );

/*  WAKE_UP
    Removes the process from the asleep process list and changes it to be ready to run or awaken
    PARAMETERS:
        Proc * proc     : Pointer to the process you want to awaken

    RETURNS:
        void            : There is no return value
*/

void wake_up (Proc *proc);