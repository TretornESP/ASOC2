
typedef struct{

} Signals;

typedef struct{
    
} Process_timer;

typedef struct{
    int state;              // Process state
    int dir;                // Direction in memory of the process
    int uid;                // User id
    int pid;                // Process id
    int awake;              // 0 awake 1 sleep
    int nice;               // Scheduling parameters
    Signals *signals;       // List of signals received but not processed
    Process_timer timers;   // Accounting
} Process_info;