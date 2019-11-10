#include <stdio.h>
#include "readline.h"

#define Name_LEN 25
#define MAX_PARTS 100

struct part
{
	int number;
	char name[Name_LEN+1];
	int on_hand;
}inventory[MAX_PARTS];

int find_part(int number);
void insert(void);
void search(void);
void update(void);
void print(void);

int num_parts = 0; /*number of parts currently stored*/

/*main*/
main(){
	char code;

	for(;;){
		printf("Enter operation code:\n");
		scanf(" %c", &code);
		while(getchar()!='\n');
		switch(code){
			case 'i': insert();
			break;
			case 's': search();
			break;
			case 'u':update();
			break;
			case 'p': print();
			break;
			case 'q': return 0;
			default: printf("Illegal code\n");
		}
		printf("\n");
	}
}

/*find_parts: Looks up a part number in the inventory array*/
int find_part(int number){
	int i;
	for(i=0; i<num_parts;i++){
		if(inventory[i].number==number){
			return i;
		}
		return -1;
	}
}

/*print insert if the part already exists or the database is full*/
void insert(void){
	int part_number;
	if(num_parts == MAX_PARTS){
		printf("Database is full!\n");
		return;
	}
	printf("Enter part number: ");
	scanf("%d", &part_number);
	if(find_part(part_number)>=0){
		printf("Part already exists\n");
		return;
	}

	inventory[num_parts].number = part_number;
	printf("Enter part name: ");
	read_line(inventory[num_parts].name, Name_LEN);
	printf("Enter quantity on hand: ");
	scanf("%d", &inventory[num_parts].on_hand);
	num_parts++;
}

/*Search: search a part by enting a part number*/
void search(void){
	int i, number;
	printf("Enter part number: ");
	scanf("%d", &number);
	i = find_part(number);
	if(i>=0){
		printf("Part name: %s\n", inventory[i].name);
		printf("Quantity on hand %d\n",inventory[i].on_hand );
	}else{
		printf("Part not found\n");
	}
}

/*Update: */