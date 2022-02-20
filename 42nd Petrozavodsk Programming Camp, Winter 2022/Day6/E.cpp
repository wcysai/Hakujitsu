#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1005
#define MAXM 5005
#define INF 1000000000000000000LL
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,T;
ll n,p;
int tmp[4];
int ask(ll x,int w)
{
	T++;
	printf("? %lld\n",x);
	fflush(stdout);
	int y;
	scanf("%d",&y);
	return y^w;
}
void answer(ll x)
{
	printf("! %lld\n",x);
	fflush(stdout);
	int y;
	scanf("%d",&y);
	assert(y==1);
}
ll get_ans(ll x)
{
	ll res=0,base=1;
	while(base<=p)
	{
		base*=n; res*=n; x=x*n%p;
		res+=tmp[x%n];
	}
	return res;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		T=0;
		scanf("%lld%lld",&n,&p);
		for(int i=0;i<n;i++) tmp[(n-i)*p%n]=i;
		ll res=0,base=1;
		while(base<=p)
		{
			base*=n; res*=n;
			res+=tmp[ask(INF,0)];
		}
		ll l=0,r=p;
		while(r-l>1)
		{
			ll mid=(l+r)/2;
			if(get_ans(mid)<=res) l=mid; else r=mid; 
		}
		if(get_ans(l)!=res)
		{
			answer(INF); continue; 
		}
		ll seed=l;
		base=1;
		while(base<=p) {base*=n; seed=seed*n%p;}
		l=0,r=INF+1;
		while(r-l>1)
		{
			ll mid=(l+r)/2;
			seed=seed*n%p;
			int x=ask(mid,seed%n);
			if(x==0) r=mid; else if(x==2) l=mid+1;
			else {l=mid; break;}
		}
		bool f=true;
		while(T<100)
		{
			seed=seed*n%p;
			if(ask(l,seed%n)!=1) {f=false; answer(INF); break;} 
		}
		if(f) answer(l);
	}
	return 0;
}