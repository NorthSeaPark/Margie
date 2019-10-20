#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <string.h>
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

int firstCapital(void *data){
	char *a = "A";
	char *z = "Z";
	if(strncmp((char*)data,"A",1)>=0&&strncmp((char*)data,"Z",1)<=0){
		return 1;
	}else{
		return 0;
	}
	
}

/*A criteria function might return true when the first character of the string is upper case. These are all easily tested.*/

int main()
{
	ActionFunction demo1 = &printString;
	demo1("New Boy");

	ComparisonFunction demo2 = &compareFirst;
	int i = demo2("asshole", "bitch");
	printf("%d\n", i);

	
	CriteriaFunction demo3 = &firstCapital;
	int n = demo3("Ass");
	printf("%d\n", n);
}