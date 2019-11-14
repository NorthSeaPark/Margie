/*桌上有一堆牌1~n,当至少还剩两张牌时，把第一张扔掉，然后把新的第一张放到牌堆最后，输出每次扔掉的牌，和最后一张牌*/
#include<cstdio>
#include<queue>
using namespace std;

queue<int> q;
int main()
{
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		q.push(i+1);
	}
	while(!q.empty()){
		printf("%d ",q.front() );
		q.pop();
		q.push(q.front());
		q.pop();
	}
	return 0;
}