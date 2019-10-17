#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct linkedlist{
	int data;
	struct linkedlist *next;
};

typedef struct linkedlist *node; /*define the node*/

node createNode(){
	node temp;
	temp = (node)malloc(sizeof(struct linkedlist));
	temp->next = NULL;
	return temp;
}

node addNode(node head, int value){
	node temp, p;
	temp = createNode();
	temp->data = value;
	if(head == NULL){
		head = temp;
	}else{
		p = head;
		while(p->next != NULL){
			p = p->next;
		}
		p->next = temp;
	}
	return head;
}

void traverse(node head){
	node temp = head;
	while(temp != NULL){
		temp = temp->next;
		printf("%d\n",temp->data);
	}
}

int main()
{
	node sb = createNode();
	sb = addNode(sb, 3);
	sb = addNode(sb, 2);
	sb = addNode(sb, 1);
	traverse(sb);
}