#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
/*Action function print the string*/
void printString(void *data){
	printf("%s\n", (char*)data);
}

/*return true when the first character of one string is greater (numerically) than the first character of the other string*/
int compareFirst(void *data1, void *data2){
	
}
int main()
{
	ActionFunction sb = &printString;
	sb("kkk");
}