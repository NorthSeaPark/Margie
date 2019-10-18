#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct linkedlist{
	int data;
	struct linkedlist *next;
};

typedef struct linkedlist *node; /*define the node*/

node createNode(int x){
	node temp;
	temp = (node)malloc(sizeof(struct linkedlist));
	temp->data = x;
	temp->next = NULL;
	return temp;
}

/*Simply put the node one by one*/
node addNode(node head, int value){
	node temp, p;
	temp = createNode(1);
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

void add(node head, int value){
	node temp = createNode(value);
	if(head = NULL){
		head = temp;
	}else{
		node p = head;
		while(p->next != NULL){
			p = p->next;
		}
		p->next = temp;
	}
}

/*Insert by order*/
node pushNode(node head, int value){
	node temp = createNode(value);
	if(head->next == NULL || head->data>value){
		if(value>=head->data){
			head->next = temp;
		}else{
			temp->next=head;
			head = temp;
		}
	}else{
			node current = head;
			while(current->next!=NULL&&current->next->data<value){
				current = current->next;
			}
			temp->next=current->next;
			current->next = temp;
	}
	return head;
}

void traverse(node head){
	node temp = head;
	while(temp != NULL){
		printf("%d\n",temp->data);
		temp = temp->next;
	}
}

int main()
{
	node sb = createNode(5);
	sb = pushNode(sb,3);
	sb = pushNode(sb,2);
	sb = pushNode(sb,4);
	sb = pushNode(sb,1);
	sb = pushNode(sb,6);
	traverse(sb);
}