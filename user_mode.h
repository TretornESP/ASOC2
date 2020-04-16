typedef struct{

} Signals;

typedef struct{

} Process_timer;

typedef struct{
    Proc * process;                 // Pointer to the start of the entry that matches this proccess in the process table
    int uid_effective;              // Effective user id
    int uid_real;                   // Real user id
    int user_execution_time;        // User mode CPU time
    int kernel_execution_time;      // Kernel CPU time
                                    // Array of functions that tells how to be interpreted each signal.
    int tty;                        // Terminal control (TTY).
    int errno;                      // Error code during syscalls.
    void * result;                  // Syscall results.
                                    // I/O parameters that indicates the amount to transfer , the source direction, offset,etc.
                                    // Current directory,
    int * open_files;               // List of file descriptors opened
                                    // Limit fields that restrict the size of a process and the size of the file they can write.
                                    // ## Mask of permissions of the files the process can create. ##
} U_entry;