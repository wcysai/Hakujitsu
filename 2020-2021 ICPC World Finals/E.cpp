#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
ll d1[MAXN],d2[MAXN],a[MAXN];
string str;
int l,r;
void add_interval(ll d[],int l,int r,int val)
{
	d[l]+=val; d[r+1]-=val;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<k;i++)
	{
		cin>>str;
		scanf("%d%d",&l,&r);
		if(str[0]=='R') add_interval(d1,l,r,1);
		else if(str[0]=='D') add_interval(d1,l,r,-1);
		else if(str[0]=='H')
		{
			add_interval(d2,l,(l+r+1)/2,1);
			add_interval(d2,(l+r+2)/2,r+1,-1);
		}
		else
		{
			add_interval(d2,l,(l+r+1)/2,-1);
			add_interval(d2,(l+r+2)/2,r+1,1);
		}
	}
	for(int i=1;i<=n;i++) {d2[i]+=d2[i-1]; d1[i]+=d2[i];}
	for(int i=1;i<=n;i++) {d1[i]+=d1[i-1]; printf("%lld\n",d1[i]);}
	return 0;
}