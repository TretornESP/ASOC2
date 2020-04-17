
#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#define ITR_SIZE             3  // Amount of interruptions
#define MAX_ITR_SIZE            // Max amount of processes stopped by a single interruption

/* It works as a queue thinking of switching stack.*/

typedef struct {
	Proc * proc;
    Itr_proc *next;
}Itr_proc;

typedef struct{
    Itr_proc *itr;  				
    int size;
}Node;

Node *Itr_table;


Itr_table itr_table_create();
int itr_table_empty (Itr_table list , int itr);
void itr_table_insert (Itr_table *list, Proc *proc , int itr);
void itr_table_clear (Itr_table list);
void itr_table_remove (Itr_table *list , Proc *proc , int itr) ;
int itr_table_search (Itr_table list , Proc *proc, int itr);
#endif
