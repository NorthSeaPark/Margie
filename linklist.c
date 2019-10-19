#include <stdio.h> 
#include <stdlib.h> 

typedef struct Node
{
	int data;
	struct Node *next;
} node;


void addNode(node *head, int value){
	node *temp = head;
	/*traverse to the last item of the linklist*/
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = malloc(sizeof(node));
	temp->next->data = value;
	temp->next->next = NULL;
}

/*insert with increasing order*/
void push(node *head, int value){
	if(head->next==NULL||head->data > value){
		if(value>=head->data){
			head->next = malloc(sizeof(node));
			temp->next->data = value;
			temp->next->next = NULL;
		}else{
			node *temp = malloc(sizeof(node));
			temp->data = value;
			temp->next = head;
			head = temp;
		}
	}else{
		node *current = head;
		while(current->next!=NULL&&current->next->data<value){
			current = current->next;
		}
		node *temp = malloc(sizeof(node));
		temp->next = current->next;
		temp->data = value;
		current->next = temp;
	}
}

void traverse(node *head){
	node *temp = head;
	while(temp!=NULL){
		printf("%d\n",temp->data);
		temp=temp->next;
	}
}

int pop(node **head) {
	int i = -1;
	node *next_node = NULL;
	if(*head == NULL){
		return -1;
	}

	next_node = (*head) -> next;
	i = (*head)->data;
	free(*head);
	*head = next_node;

	return i;
}

int main()
{
	/*Create a node*/
	node *head = malloc(sizeof(node));
	head->data = 10;
	head->next = NULL;

	/*Add nodes*/
	addNode(head,9);
	addNode(head,8);

	/*print nodes*/
	traverse(head);
	int outcome =  pop(&head);
	printf("pop out %d\n",outcome);
	traverse(head);
}