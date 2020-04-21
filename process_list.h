#ifndef PROCLIST_H_INCLUDED
#define PROCLIST_H_INCLUDED

#define TABLE_PROC_SIZE 		1048

/*
    The following structures are implementing a linked list that acts as a stack
    to store the all the processes.
    On the future we may think of implement it so it acts as a queue
*/

typedef struct {
	Proc *proc;
	int num_procs;
	Nodet *next;
}Node_proc;

typedef Node_proc * Process_table;

/*  TABLE_PROC_CREATE
    Creates a process table and allocates memory for it.
    PARAMETERS:

    RETURNS:
        Process_table       	: Pointer to the new table.
*/

Process_table table_proc_create();

/*  TABLE_PROC_INSERT
    Inserts a process into the list.
    PARAMETERS:
		Process_table * list    : Process list.
        int itr             	: Process pointer to add.

    RETURNS:
        void                	: There is no return value
*/

void table_proc_insert(Process_table * table, Proc *proc);

/*  TABLE_PROC_EMPTY
    Returns if the size of the table for a given interrupt is equal to zero.
    PARAMETERS:
        Process_table * list    : Process list.
        int itr             	: Interrupt identifier.

    RETURNS:
        int                 	: Returns 0 if it's empty, otherwise returns 1.
*/

int table_proc_empty(Process_table table);

/*  TABLE_PROC_REMOVE
    Removes a process from the list.
    PARAMETERS:
        Process_table * list    : Process list.
        Proc * proc         	: Process to remove.
        int itr             	: Interrupt identifier.

    RETURNS:
        void                	: There is no return value
*/

void table_proc_remove(Process_table table);

/*  TABLE_PROC_SEARCH
    Searchs a process in the list with a given interrupt.
    PARAMETERS:
        Process_table * list    : Process list.
        Proc * proc         	: Process to remove.
        int itr             	: Interrupt identifier.

    RETURNS:
        int                 	: Returns 0 if not found, otherwise returns 1.
*/

int Process_table_search (Process_table list , Proc *proc, int itr);

#endif