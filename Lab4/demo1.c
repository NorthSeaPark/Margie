#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	printf("loose\n");
	FILE * input;
	input = fopen("infile.txt","r");
	int i, n, m;
	while(fscanf(input,"%d %d %d", &i, &n, &m)==3){
		printf("%d %d %d\n",i, n, m);
	}
	fclose(input);
}