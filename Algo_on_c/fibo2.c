#include <stdio.h>
int fibo2 (int n);

int fibo2(int n){
	int rv;
	rv = n;
	if (rv >= 2)
	{
		int partial, param;
		param = n-1;
		partial = fibo2(param);
		param -= 1;
		rv = fibo2(param);
		rv += partial;
	}
	return rv;
}

int main(){
	int i = fibo2(2);
	printf("%d\n",i );
}