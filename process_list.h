#ifndef PROCLIST_H_INCLUDED
#define PROCLIST_H_INCLUDED

#define TABLE_PROC_SIZE 		1048

typedef struct {
	Proc *proc;
	int num_procs;
	Nodet *next;
}Node_proc;

typedef Node_proc *Process_table;

Process_table create_table();
void table_proc_insert(Process_table* table, Proc *proc);
int table_proc_empty(Process_table table);
void table_proc_remove(Process_table table);

#endif