#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <string.h>

/*This is for the prototype2: implement and test the insert and traverse functions*/
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
void traverse(Node *head, ActionFunction doThis){
	Node *temp = head;
	while(temp!=NULL){
		printf("%s\n",(char*)temp->data);
		temp=temp->next;
	}
}

/*Insert Function*/
int insert(Node **p2head, void *data, ComparisonFunction goesInFrontOf){
	if((*p2head)->next==NULL||goesInFrontOf((*p2head)->data,data)>0){
		if(goesInFrontOf(data,(*p2head)->data)>=0){
			(*p2head)->next = malloc(sizeof(Node));
			(*p2head)->next->data = data;
			(*p2head)->next->next = NULL;
		}else{
			Node *temp = malloc(sizeof(Node));
			temp->data = data;
			temp-> next = *p2head;
			*p2head = temp;
		}
	}else{
		Node *current = *p2head;
		while(current->next!=NULL&&goesInFrontOf(current->next,data)<0){
			current = current->next;
		}
		Node *temp = malloc(sizeof(Node));
		temp->next = current->next;
		temp->data = value;
		current->next = temp;
	}
}

