
#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#define ITR_SIZE             3  // Amount of interruptions
#define MAX_ITR_SIZE            // Max amount of processes stopped by a single interruption

/*
    The following structures are implementing a linked list that acts as a stack
    to store the processes that are asleep, grouping them by the interrupt that caused
    it to switched to asleep.
    On the future we may think of implement it so it acts as a queue
*/
typedef struct {
	Proc * proc;
    Itr_proc *next;
}Itr_proc;

typedef struct{
    Itr_proc *itr;  				
    int size;
}Node;

Node *Itr_table;

/*  ITR_TABLE_CREATE
    Creates a Interrupt table and allocates memory for it.
    PARAMETERS:

    RETURNS:
        Itr_table           : Pointer to the new table.
*/

Itr_table itr_table_create();

/*  ITR_TABLE_EMPTY
    Returns if the size of the table for a given interrupt is equal to zero.
    PARAMETERS:
        Itr_table * list    : Asleep process list.
        int itr             : Interrupt identifier.

    RETURNS:
        int                 : Returns 0 if it's empty, otherwise returns 1.
*/

int itr_table_empty (Itr_table list , int itr);

/*  ITR_TABLE_INSERT
    Inserts a process to the list with a given interrupt.
    PARAMETERS:
        Itr_table * list    : Asleep process list.
        Proc * proc         : Process to add.
        int itr             : Interrupt identifier.

    RETURNS:
        void                : There is no return value
*/

void itr_table_insert (Itr_table *list, Proc *proc , int itr);

/*  ITR_TABLE_CLEAR
    Removes all elements of the given list.
    PARAMETERS:
        Itr_table * list    : Asleep process list.

    RETURNS:
        void                : There is no return value
*/

void itr_table_clear (Itr_table list);

/*  ITR_TABLE_REMOVE
    Removes a process to the list with a given interrupt.
    PARAMETERS:
        Itr_table * list    : Asleep process list.
        Proc * proc         : Process to remove.
        int itr             : Interrupt identifier.

    RETURNS:
        void                : There is no return value
*/

void itr_table_remove (Itr_table *list , Proc *proc , int itr) ;

/*  ITR_TABLE_SEARCH
    Searchs a process in the list with a given interrupt.
    PARAMETERS:
        Itr_table * list    : Asleep process list.
        Proc * proc         : Process to remove.
        int itr             : Interrupt identifier.

    RETURNS:
        int                 : Returns 0 if not found, otherwise returns 1.
*/

int itr_table_search (Itr_table list , Proc *proc, int itr);
#endif
