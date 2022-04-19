#include<bits/stdc++.h>
#define MAXN 205
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
int t;
db x;
db fact[MAXN];
db comb(int n,int k)
{
	return fact[n]-fact[k]-fact[n-k];
}
int main()
{
	fact[0]=0;
	for(int i=1;i<=200;i++) fact[i]=fact[i-1]+log(i);
	scanf("%d",&t);
	while(t--)
	{
		scanf("%Lf",&x);
		db ans=1.0;
		db inv=1.0/x;
		for(int n=1;n<=200;n++)
		{
			db res=0.0;
			for(int i=0;i<=n;i++)
			{
				if(i>=inv) break;
				db tmp=n*log(inv-i); tmp-=fact[i]; tmp-=fact[n-i];
				if(i&1) res-=exp(tmp); else res+=exp(tmp);
			}
			ans+=res;
		}
		printf("%.15Lf\n",ans);
	}
	return 0;
}