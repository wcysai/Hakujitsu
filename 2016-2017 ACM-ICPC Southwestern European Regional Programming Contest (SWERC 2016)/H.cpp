#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int d,h;
ll fact[MAXN];
int pcnt[MAXN];
vector<int> pr={2,3,5,7,11,13,17,19,23,29,31};
void add(int x)
{
	for(auto p:pr)
	{
		int cnt=0,tmp=x;
		while(tmp) cnt+=tmp/p,tmp/=p;
		pcnt[p]+=cnt;
	}
}
void dec(int x)
{
	for(auto p:pr)
	{
		int cnt=0,tmp=x;
		while(tmp) cnt+=tmp/p,tmp/=p;
		pcnt[p]-=cnt;
	}
}
ll calc()
{
	ll x=1;
	for(auto p:pr)
	{
		for(int j=0;j<pcnt[p];j++) x*=p;
	}
	return x;
}
set<ll> s;
void dfs(int now,int sum,int last)
{
	if(now==d)
	{
		if(sum==h-1) s.insert(calc());
		return;
	}
	for(int i=last;(d-now)*i+sum<=h-1;i++) 
	{
		dec(i);
		dfs(now+1,sum+i,i);
		add(i);
	}
}
int main()
{
	fact[0]=1;
	for(int i=1;i<=31;i++) fact[i]=1LL*fact[i-1]*i;
	scanf("%d%d",&d,&h);
	add(h-1);
	dfs(0,0,0);
	for(auto x:s) printf("%lld\n",x);
	return 0;
}