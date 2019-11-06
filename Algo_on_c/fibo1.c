#include <stdio.h>

int fibo(int n);

int fibo(int n){
	if (n<=2)
	{
		return 1;
	}else{
		return fibo(n-1) + fibo(n-2);
	}
}

int main(){
	int i = fibo(4);
	printf("%d\n",i );
}