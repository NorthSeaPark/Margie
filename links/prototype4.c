#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <string.h>

/*This is for the prototype3: implement and test delete functions*/
/*in this case, I added file arguments, allocateNode function and freeNode function*/

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


/*Allocate Function*/
/*For this case, we just allocate one node*/
Node* allocateNode(FILE *diagnostics, void *data){
	Node * new_node = malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;
	diagnostics = fopen ("diagnostics.txt", "a+");
	fprintf(diagnostics, "Diagnostic: %s %s %d %s\n", "We", "allocate", 1, "node");
	fclose(diagnostics);
	return new_node;
}

/*Free Node fuction*/
void freeNode(Node *temp, FILE *diagnostics){
	free(temp);
	diagnostics = fopen ("diagnostics.txt", "a+");
	fprintf(diagnostics, "Diagnostic: %d %s %s %s\n", 1, "node", "is", "free");
	fclose(diagnostics);
}


/*Traverse Functions*/
/*Need implement with diagnostic*/
void traverse(Node *head, ActionFunction doThis, FILE *diagnostics){
	Node *temp = head;
	diagnostics = fopen ("diagnostics.txt", "a+");
	fprintf(diagnostics, "Bellow are the nodes in order:\n");
	fclose(diagnostics);
	while(temp!=NULL){
		doThis(temp->data);
		diagnostics = fopen ("diagnostics.txt", "a+");
		fprintf(diagnostics, "The node: %s\n",(char*)(temp->data));
		fclose(diagnostics);
		temp=temp->next;
	}
}

/*Insert Function*/

int insert(Node **p2head, void *data, ComparisonFunction goesInFrontOf, FILE *diagnostics){
	Node * new_node = allocateNode(diagnostics, data);

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
void deleteSome(Node **p2head, CriteriaFunction mustGo, ActionFunction disposal, FILE *diagnostics){
	Node *temp = *p2head, *prev;
	while(temp != NULL && mustGo(temp->data)==1){
		disposal(temp->data);
		*p2head = temp->next;
		freeNode(temp,diagnostics);
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
		freeNode(temp,diagnostics);
		temp = prev->next;
	}
}

int main()
{
	ActionFunction demo1 = &printString;
	ComparisonFunction demo2 = &compareFirst;
	CriteriaFunction demo3 = &firstCapital;
	FILE *diagnostics;
	Node *head = NULL;
	insert(&head,"C", demo2, diagnostics);
	insert(&head,"b", demo2, diagnostics);
	insert(&head,"A", demo2, diagnostics);
	deleteSome(&head, demo3, demo1, diagnostics);
	printf("Above are the deleted nodes\n");
	printf("Bellow are the nodes left\n");
	traverse(head, demo1, diagnostics);
}

