#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,s;
P p[MAXN];
bool check(int x,int y)
{
	int a=p[x].F+(s-p[x].S),b=p[y].F;
	if(a==b) return true;
	int c=p[x].F,d=(p[y].F+s-p[y].S);
	if(c==d) return true;
	if((a<b?1:0)!=(c<d?1:0)) return false; else return true;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		s=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&p[i].F,&p[i].S);
			s+=p[i].S;
		}
		if(n==2) {puts("Yes"); continue;}
		bool f=true;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				if(!check(i,j)) 
					f=false;
		if(f) puts("Yes"); else puts("No");
	}
	return 0;
}