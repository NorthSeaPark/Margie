#include <stdio.h>
long f(long n);

main(){
	long input, output;
	printf("Enter: ");
	scanf("%ld", &input);
	output = f(input);
	printf("%ld\n", output);
}