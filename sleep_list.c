#include "sleep_list.h"

/*usar custom malloc. custom free*/

Itr_table itr_table_create(){
	int i;
	Itr_table* list = malloc(sizeof(ITR_SIZE * Node));

	for (i = 0; i < ITR_SIZE; i++){
		(*list)[i]->itr = malloc(sizeof(Itr_proc));
		(*list)[i]->itr->proc= NULL;
		(*list)[i]->itr->next= NULL;
		(*list)[i]->size = 0;
	}
	return list;
}

int itr_table_empty (Itr_table list , int itr){
	return (list[i]->size == 0);
}

void itr_table_insert (Itr_table *list, Proc *proc , int itr){

	if(list[i]->size < MAX_SIZE_ITR){
		Itr_proc *current = list[i]->itr;
		Itr_proc aux = malloc (sizeof(Itr_proc));
		aux->proc= proc;
		aux->next = NULL;

		while(current->next != NULL){
			current = current->next;
		}

		current->next = aux;
		(*list)[i]->size++;

	}else{
		perror("Not enough memory on sleep list");
	}
}

void itr_table_clear (Itr_table *list) {
	int i;
	Itr_proc *current,aux;
	for (i = 0; i < ITR_SIZE; i++){
		current = list[i]->itr;
		while(current->next != NULL){
			aux = current;
			current = current->next;
			free(aux);
		}
		free(current);
		list[i]->size = 0;
	}
}

void itr_table_remove (Itr_table *list , Proc *proc , int itr) {
	if (!itr_table_empty(*list , itr)){
		Itr_proc *current = list[i]->itr;
 		Itr_proc *previous , *next , *toret;
		previous = current;
		next = current->next;

		while ( (current->next != NULL) && (current->proc != proc) ){
			previous = current;
			current = current->next;
			next = current->next;
		}
		if ( (current->proc != proc) && (current->next == NULL ) ){
			perror("That process does not exist.\n");
			return;
		} else {
			previous->next = next;
			free(current);
			list[i]->size--;
			return;
		}
	} else {
		perror("The sleep list is Empty.\n");
	}
	
}

int itr_table_search (Itr_table list , Proc *proc, int itr){

	Itr_proc aux = list[i]->itr; 
	while ( (aux != NULL) && (aux->proc != proc) ){
		aux = aux->next;
	}

	if (aux == NULL){
		return 0;
	} else{
		return 1;
	}
}