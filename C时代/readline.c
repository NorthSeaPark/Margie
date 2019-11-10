#include <ctype.h>
#include <stdio.h>
#include "readline.h"

int read_line(char str[], int n){
	int ch, i=0;
	while(isspace(ch = getchar()))
		;
	/*isspace用来判断他的实际参数是否是空白字符*/
	while(ch!='\n'&&ch!=EOF){
		if(i<n){
			str[i++] = ch;
		}
		ch = getchar();
	}
	str[i] = '\0';
	return i;
}
/*\0 is always at the end of a string*/