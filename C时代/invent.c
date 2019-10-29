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

/*main*/