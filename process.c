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

extern void cli();                                      // Blocks all incoming interruptions
extern void sti();                                      // Unblocks interruptions


int sleep ( int itr , Proc *proc , int priority ){
    cli();												//Block all interrumptions Hardware
    if(!process_to_sleep(proc))                   	    // Put a process to sleep
        return 0;
    
    insert_List(list, proc, itr);                    	// Adds the process to the slept processes list

    if (!setPriority_process(priority,proc)){
        perror("Priority could not be changed.\n");
    }

    if (!pro->is_interrumpable){                     
        switch_context();                           	// Process resumes the execution when it wakes up   
        pro->is_interrumpable = TASK_INTERRUPTIBLE	    // Unblocks all interruptions
        sti();											// unlock hardware Interrupts
        return 0;
    }

    if (proc->signals == NULL){                     	// No signal pending against the process
        switch_context();                           	// Process resumes the execution when it wakes up 
        if (proc->signals == NULL){
            setPriority_process(priority,proc);
            return 0;
        }
    }

    if(search_itr_proc(list,proc,itr)){
        remove_proc(list,proc,itr);                    		// Removes the process from the list
    }

    if(proc->is_interrumpable == TASK_INTERRUPTIBLE) {
        return 1;
    }                      
}

int process_to_sleep(Proc *proc){
    int toret = 0;
    proc->state = WAITING;
    if (proc == WAITING){
        toret = 1;
    }else {
        perror("The process did not go to sleep.\n");
    }
    return toret;
}

int setPriority_process (int priority , Proc *proc ){
	int toret = 0;
	proc->priority = priority;

	if (proc->priority == priority){
		toret = 1;
	}else {
        perror("The priority process could not be changed.\n");
    }
	return toret;
}

int sleep (  Proc *proc , int priority ){

    pushcli();                                      // Blocks all interruptions
    process_to_sleep(proc);                         // Put a process to sleep 
    insert_sleepList(proc,list);                    // Adds the process to the slept processes list

    if (process is not interrumptable){                     
        switch_context();                           // Process resumes the execution when it wakes up   
        popcli();                                   // Unblocks all interruptions
        return 0;
    }

    if (proc->signals == NULL){                     // No signal pending against the process
        switch_context();                           // Process resumes the execution when it wakes up 
    }

    remove_sleepList(proc,list);                    // Removes the process from the list

    if(proc->state == AWAKEN) return 1;
    
    longjmp_algorithm();                        
}

void wake_up (Proc *proc){
    
    pushcli();                                      // Blocks all interruptions
    remove_sleepList(proc,list);                    // Removes the process from the list 
    proc->state = READY_TO_RUN;                     // Set the process state for READY_TO_RUN
    insert_schedulerList(process);                  // Linked List Elligible process
    if(proc->state == ASLEEP){                      // If the process is asleep, but isn't allocated in memory
        swap_in(proc);                              // Kernel swap the process into RAM
    } else{
        scheduler();                                // Decide which process to run after waking this one up
    } 
    popcli();                                       // Unblock all interrupts
}