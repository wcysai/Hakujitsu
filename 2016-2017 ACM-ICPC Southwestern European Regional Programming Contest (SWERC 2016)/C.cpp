#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int d,x,y;
int main()
{
	scanf("%d%d%d",&d,&x,&y);
	for(int i=d;i<=100;i++)
	{
		int sum=0;
		int l=4,r=i;
		if(l<=r) sum+=1LL*(l+r)*(r-l+1)/2;
		l=3,r=i-d;
		if(l<=r) sum+=1LL*(l+r)*(r-l+1)/2;
		if(sum==x+y)
		{
			printf("%d\n",1LL*(l+r)*(r-l+1)/2-y);
			return 0;
		}
	}
	return 0;
}