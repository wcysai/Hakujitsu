#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll s[MAXN];
int n;
ll k;
ll get(int x)
{
	return 1LL*x*(x-1)/2;
}
P valid(int n,ll x)
{
	int l=0,r=n/2+1;
	while(r-l>1)
	{
		int mid=(l+r)/2;
		if(get(mid)+get(n-mid)>=x) l=mid; else r=mid;   
	}
	if(get(l)+get(n-l)==x) return P(l,n-l); else return P(-1,-1);
}

ll get_min_3(int n)
{
	if(n<=2) return 0;
	int x=(n+1)/3,mod=(n+1)%3;
	return (3-mod)*get(x)+mod*get(x+1);
}
ll get_min_2(int n)
{
	int x=n/2,mod=n%2;
	return (2-mod)*get(x)+mod*get(x+1);
}
int main()
{
	scanf("%d%lld",&n,&k);
	if(k>get(n+1)||k<get_min_3(n)) {puts("-1"); return 0;}
	int id=-1;
	for(int i=0;i<=n;i++)
	{
		ll val=get(i+1);
		if(k>=val&&valid(n-i,k-val).F!=-1) id=i; 
	}
	if(id==-1) {puts("-1"); return 0;}
	k-=get(id+1);
	P p=valid(n-id,k);
	swap(p.F,p.S);
	for(int i=id+1;i<=id+p.F;i++) s[i]=1;
	for(int i=id+p.F+1;i<=n;i++) s[i]=2;
	for(int i=1;i<=n;i++) printf("%d ",(s[i]-s[i-1]));
	return 0;
}