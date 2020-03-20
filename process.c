/*
Changes the state of the process from:
    ASLEEP_IN_MEM   ->  READY_TO_RUN
    KERNEL_RUNNING  ->  ASLEEP_IN_MEM

Usually gets called due to a syscall,a context switch is needed afterwards.
Another reason can be a pagination error, and it's not in memory.

If an event occurs they leave the ASLEEP_IN_MEM state, they change to AWAKEN into READY_TO_RUN.
Then we put it back in virtual memory. This events are supposed to be in the kernel
and have asigned a specific memory direction.

When a process waits for the buffer has to wait for the I/O to finish. While it's not done
they will be in the ASLEEP_IN_MEM state.

*/

int sleep (  Proc *proc , int priority ){

    pushcli();                                      // Blocks all interruptions
    process_toSleep(proc);                          // Put a process to sleep 
    insert_SleepList(proc,list);                    // Adds the process to the slept processes list

    if (process is not interrumptable){                     
        switch_context();                           // Process resumes the execution when it wakes up   
        popcli();                                   // Unblocks all interruptions
        return 0;
    }

    if (proc->signals == NULL){                     // No signal pending against the process
        switch_context();                           // Process resumes the execution when it wakes up 
    }

    remove_SleepList(proc,list);                    // Removes the process from the list

    if(proc->state == AWAKEN) return 1;
    
    longjmp_algorithm();                        
}

void wake_up (Proc *proc){
    
    pushcli();                                      // Blocks all interruptions
    remove_SleepList(proc,list);                    // Removes the process from the list 
    proc->state = READY_TO_RUN;                     // Set the process state for READY_TO_RUN
    insert_SchedulerList(process);                  // Linked List Elligible process
    if(proc->state == ASLEEP){                      // If the process is asleep, but isn't allocated in memory
        swap_in(proc);                              // Kernel swap the process into RAM
    } else{
        scheduler();                                // Decide which process to run after waking this one up
    } 
    popcli();                                       // Unblock all interrupts
}