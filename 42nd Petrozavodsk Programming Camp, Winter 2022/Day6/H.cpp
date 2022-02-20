#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int fact[MAXN],invf[MAXN];
int pow_mod(int a,int i)
{
    if(i==0) return 1;
    int s=1;
    while(i>0)
     {
         if(i&1) s=(1LL*s*a)%MOD;
         a=(1LL*a*a)%MOD;
         i>>=1;
     }
     return s;
}
int inv(int x)
{
	return pow_mod(x,MOD-2);
}
int comb(int n,int k)
{
	if(n<k) return 0;
	return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	fact[0]=invf[0]=1;
	for(int i=1;i<=200000;i++)
		fact[i]=1LL*fact[i-1]*i%MOD;
	invf[200000]=pow_mod(fact[200000],MOD-2);
	for(int i=199999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
	int ans=0;
	for(int k=0;k<=m;k++)
	{
		int res=(1LL*fact[m]*invf[k]%MOD*invf[m-k])%MOD*pow_mod(m-k,n+m)%MOD;
		if(!(k&1)) ans=(ans+res)%MOD; else ans=(ans+MOD-res)%MOD;
	}
	ans=1LL*ans*invf[m]%MOD;
	ans=1LL*ans*fact[n]%MOD*fact[m-1]%MOD*invf[n+m-1]%MOD;
	printf("%d\n",ans);
}