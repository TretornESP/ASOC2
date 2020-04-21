#include <process_list.h>

Process_table table_proc_create(){
	Process_table* table = malloc(sizeof(Node_proc));
	(*table)->proc = NULL;
	(*table)->next = NULL;
	(*table)->num_procs = 0;
	return table;
}

void table_proc_insert(Process_table* table, Proc *proc){
	if(table->num_procs == TABLE_PROC_SIZE){
		perror("The table process is full.\n");
	}else {
		Process_table *current = table;
		Process_table aux = malloc(sizeof(Node_proc));
		aux->proc = proc;
		aux->next = NULL;

		while((*current)->next != NULL){
			current = (*current)->next;
		}
		(*current)->next = aux;
		(*current)->num_procs++;
	}
}

int table_proc_empty(Process_table table){
	return table->num_procs == 0;
}

void table_proc_remove(Process_table table){
	Process_table aux = table->next, aux2;

	while(aux != NULL){
		aux2 = aux;
		aux = aux->next;
		free(aux2);
	}
	free(table);
}