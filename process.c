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
    
    itr_table_insert(list, proc, itr);                    	// Adds the process to the slept processes list

    if (!process_set_priority(priority,proc)){
        perror("Priority could not be changed.\n");
    }

    if (!pro->is_interrumpable){                     
        switch_context();                           	// Process resumes the execution when it wakes up   
        pro->is_interrumpable = PROCESS_UNINTERRUPTIBLE	    // Unblocks all interruptions
        sti();											// unlock hardware Interrupts
        return 0;
    }

    if (proc->signals == NULL){                     	// No signal pending against the process
        switch_context();                           	// Process resumes the execution when it wakes up 
        if (proc->signals == NULL){
            process_set_priority(priority,proc);
            return 0;
        }
    }

    if(itr_table_search(list,proc,itr)){
        itr_table_remove(list,proc,itr);                    		// Removes the process from the list
    }

    if(proc->is_interrumpable == PROCESS_UNINTERRUPTIBLE) {
        return 1;
    }                      
}

int process_to_sleep(Proc *proc){
    int toret = 0;
    proc->state = ASLEEP;
    if (proc == ASLEEP){
        toret = 1;
    }else {
        perror("The process did not go to sleep.\n");
    }
    return toret;
}

int process_set_priority (int priority , Proc *proc ){
	int toret = 0;
	proc->priority = priority;

	if (proc->priority == priority){
		toret = 1;
	}else {
        perror("The priority process could not be changed.\n");
    }
	return toret;
}

void wakeup (itr_table *sleep_list ,int itr, Proc* current){
    Proc *proc;
    cli();  //raise processor execution level to block all interrupts
    if(!itr_table_empty (sleep_list, itr)){    /*sleepQ = findHashQ(addr);*/  //find sleep hash queue for sleep address
        for(int i = 0; i<sleep_list.size; i++){    //for every process in the sleep hash queue ->
            proc = sleep_list-> itr[itr] ->proc[i];
            if(proc->state == ASLEEP){         ¡// -> that is asleep
                proc->state=READY_TO_RUN;
                insert_schedulerList(proc);
                itr_table_remove(sleep_list, proc, itr);
                if(!table_proc_search(proc)){ //el proceso no esta en memoria  ACORDARSE CAMBIAR CUANDO SEARCH
                    swap_in(proc);  // Kernel swap the process into RAM
                }else if(proc->priority < current->priority){  /*procesp actual es mas elegible para correr (prioridad mas alta)*/
                    set_scheduler_flag();    //set scheduler flag to indicate which is more eligible
                }
            }
        }
    }   
    sti();   //restore processor's original exe lvl (Unblock all interrupts)

}
