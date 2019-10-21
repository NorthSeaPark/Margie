#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
int sos = 1;

typedef struct 
{
	char *word;
	char *meaning;
}Words;

/*Let's build a structure*/
 Words build_word(char *a, char *b){
 	Words w;
 	w.word = a;
 	w.meaning = b;
 	return w;
 }

 void print_word(Words w){
 	printf("Word: %s\n", w.word);
 	printf("Meaning: %s\n", w.meaning);
 	printf("\n");
 }

 /*Now design a function which can add Words in an array of Words*/
 void insert_words(Words *book){
 	int size = N;
 	int i = 0;
 	while(1){
 		char a[100], b[100];
 		int q;
 		printf("Enter the word:\n");
 		scanf("%s",a);
 		printf("Enter the meaning\n");
 		scanf("%s",b);
 		Words w = build_word(a, b);

 		if(i == size){
 			size *= 2;
 			book = (Words*)realloc(book, size); 
 		}
 		

 		*(book+i) = w;
 		i = i+1;

 		printf("Do you want to quit? 1 for quit, 0 for continue: \n");
 		scanf("%d", &q);
 		if(q==1){
 			break;
 		}
 	}
 }

 /*We also need a write function*/
 int sum(int i, int sos){
 	sos = sos + i;
 	return N;
 }

 void prinfFile(File *diagonostics){
 	diagnostics = fopen ("diagnostics.txt", "w+");
	fprintf(diagnostics, "%s %s %d %s", "We", "allocate", 1, "node");
	fclose(diagnostics);
 }


int main()
{
	/*Now build an array to store these structure*/
	File *diagnostics;
	prinfFile(diagonostics);
}