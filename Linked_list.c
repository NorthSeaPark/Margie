#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typdef struct node
{
	int data;
	struct node *next;
}demo;


int main()
{
	demo *head = NULL;
	if(head == NULL){
		return 1;
	}
	head -> data = 1;
	head -> next = malloc (sizeof(demo));
	head -> next -> data = 3;
	head -> next -> next = NULL;
	/*creating a linklist with data 1 and 3*/
}

/*Method to print Java*/
void traverse(demo *head){
	demo *current = head;
	printf("%d\n", current->data );
	while(current -> next != NULL){
		current = current -> next;
		printf("%d\n", current->data );
	}
}

/*insert node in a the linked list in increasing order*/
void push(demo *head, int value){
	demo *current = head;
	if(current -> next == NULL){
		if(current -> data <= value){
			current->next = malloc(sizeof(demo));
			current->next->data = value;
			current->next->next = NULL;
		}else{
			demo *head1 = NULL;
			head1->data = value;
			head1->next = current;
			current = head1;
		}
	}
	while(current->next != NULL){
		if(value <= current->data){
			demo *head1 = NULL;
			head1->data = value;
			head1->next = current;
			current = head1;
		}else{
			current = current->next;
			if(current->next == NULL){
				if(value <= current->data){
					demo *head1 = NULL;
					head1->data = value;
					head1->next = current;
					current = head1;
					break;
				}else{
					current->next = malloc(sizeof(demo));
					current->next->data = value;
					current->next->next = NULL;
					break;
				}
			}
		}

	}
}

/*Use Recursive*/
void push1(demo *head, int value){
	if(head->next == NULL){
		if(current -> data <= value){
			current->next = malloc(sizeof(demo));
			current->next->data = value;
			current->next->next = NULL;
		}else{
			demo *head1 = NULL;
			head1->data = value;
			head1->next = current;
			current = head1;
		}
	}else{
		push1(head->next, value);
	}
}