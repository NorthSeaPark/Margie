#include <ctype.h>
#include <stdio.h>
#include "readline.h"

int read_line(char str[], int n){
	int ch, i=0;
	while(isspace(ch = getchar()))
		;
	/*isspace用来判断他的实际参数是否是空白字符*/
}