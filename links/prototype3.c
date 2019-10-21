#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <string.h>

/*This is for the prototype3: implement and test delete functions*/
/*in this case, I neglect the File argument*/

/*Action function print the string*/
void printString(void *data){
	printf("%s\n", (char*)data);
}

/*return true when the first character of one string is greater (numerically) than the first character of the other string*/
int compareFirst(void *data1, void *data2){
	int i = strncmp((char*)data1, (char*)data2, 1);
	if(i>0){
		return 1;
	}else{
		return 0;
	}
}

/*A criteria function might return true when the first character of the string is upper case. These are all easily tested.*/
int firstCapital(void *data){
	char *a = "A";
	char *z = "Z";
	if(strncmp((char*)data,"A",1)>=0&&strncmp((char*)data,"Z",1)<=0){
		return 1;
	}else{
		return 0;
	}	
}

/*Traverse Functions*/
void traverse1(Node *head, ActionFunction doThis){
	Node *temp = head;
	while(temp!=NULL){
		doThis(temp->data);
		temp=temp->next;
	}
}

/*Insert Function*/

int insert1(Node **p2head, void *data, ComparisonFunction goesInFrontOf){
	Node * new_node = malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;

	if(*p2head==NULL||goesInFrontOf((*p2head)->data,new_node->data)>=0)
	{
		new_node->next = *p2head;
		*p2head = new_node;
		return 1;
	}
	else{
		Node *current = *p2head;
		while(current->next!=NULL&&goesInFrontOf(current->next->data,new_node->data)<0){
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
		return 1;
	}
	return 0;
}

/*Delete Function*/
/*Detete All of strings start with capital letter*/
void deleteSome1(Node **p2head, CriteriaFunction mustGo, ActionFunction disposal){
	Node *temp = *p2head, *prev;
	while(temp != NULL && mustGo(temp->data)==1){
		disposal(temp->data);
		*p2head = temp->next;
		free(temp);
		temp = *p2head;
	}

	while(temp!=NULL){
		while(temp!=NULL&&mustGo(temp->data)==0){
			prev = temp;
			temp = temp->next;
		}

		if(temp==NULL) return;

		disposal(temp->data);
		prev->next = temp->next;
		free(temp);
		temp = prev->next;
	}
}

int main()
{
	ActionFunction demo1 = &printString;
	ComparisonFunction demo2 = &compareFirst;
	CriteriaFunction demo3 = &firstCapital;
	Node *head = NULL;
	int i = insert1(&head,"C", demo2);
	printf("%d\n", i);
	int n = insert1(&head,"b", demo2);
	printf("%d\n", n);
	int s= insert1(&head,"A", demo2);
	printf("%d\n", s);
	deleteSome1(&head, demo3, demo1);
	printf("Above is/are the deleted nodes\n");
	printf("Bellow is/are the nodes left\n");
	traverse1(head, demo1);
}

