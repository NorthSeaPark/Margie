#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <string.h>

int main()
{
	FILE * fp;
	fp = fopen ("file.txt", "w+");
	if(fp == NULL){
		puts("I'm wasting my life on these shits");
	}else{
		fprintf(fp, "You know I cherish u my love\n");
		fclose(fp);
	}
	return(0);
}