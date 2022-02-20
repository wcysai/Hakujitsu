#include<bits/stdc++.h>
#define MAXN 10
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,k;
int a[MAXN][MAXN];
int d[MAXN][MAXN],deg[MAXN];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&k);
		if(n==k||n==k+2) {puts("-1"); continue;}
		if(k==0)
		{
			if(n==4)
			{
				printf("%d\n%d %d\n%d %d\n%d %d\n%d %d\n",4,1,2,2,3,3,4,1,4);
			}
			else if(n==5)
			{
				printf("%d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n",5,1,2,2,3,3,4,4,5,1,5);
			}
			else if(n==6)
			{
				printf("%d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n",7,1,2,1,3,2,5,3,5 ,1,4,4,6,5,6);
			}
			else if(n&1)
			{
				printf("%d\n",3*((n-1)/2));
				for(int i=2;i<=n;i+=2) printf("%d %d\n%d %d\n%d %d\n",1,i,1,i+1,i,i+1);
			}
			else 
			{
				printf("%d\n",3*((n-1)/2)+2);
				for(int i=2;i<=n-1;i+=2) printf("%d %d\n%d %d\n%d %d\n",1,i,1,i+1,i,i+1);
				printf("%d %d\n%d %d\n",1,n,n-1,n);
			}
		}
		else
		{
			int num=n-k;
			if(num&1)
			{
				printf("%d\n",k+(num-1)+(num-1)/2);
				for(int i=1;i<=k;i++) printf("%d %d\n",i,k+1);
				for(int i=k+2;i<=n;i+=2) printf("%d %d\n%d %d\n%d %d\n",k+1,i,k+1,i+1,i,i+1);
			}
			else
			{
				printf("%d\n",k+(num-1)+(num-2)/2+1);
				for(int i=1;i<=k;i++) printf("%d %d\n",i,k+1);
				for(int i=k+2;i<=n-1;i+=2) printf("%d %d\n%d %d\n%d %d\n",k+1,i,k+1,i+1,i,i+1);
				printf("%d %d\n%d %d\n",n-1,n,k+1,n);
			}
		}
	}
	return 0;
}