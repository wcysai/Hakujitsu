#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000
#define MOD 1000000007
#define INV 500000004
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int f[MAXN],g[MAXN];
ll n,k;
int sum(ll x) {return 1LL*(x%MOD)*((x+1)%MOD)%MOD*INV%MOD;}
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int prime[MAXN];
bool is_prime[MAXN];
int sieve(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) prime[p++]=i;
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
ll PrimeCount(ll n)
{
    ll i,j,m=0;
    for(m=1;m*m<=n;m++) f[m]=sum(n/m),dec(f[m],1);
    for(i=2;i<=m;i++) g[i]=sum(i),dec(g[i],1);
    for(i=2;i<=m;i++)
    {
        if(g[i]==g[i-1]) continue;
        for(j=1;j<=min(m-1,n/i/i);++j)
        {
            if(i*j<m) dec(f[j],1LL*i*(f[i*j]-g[i-1]+MOD)%MOD);
            else dec(f[j],1LL*i*(g[n/i/j]-g[i-1]+MOD)%MOD);
        }
        for(j=m;j>=i*i;j--) dec(g[j],1LL*i*(g[j/i]-g[i-1]+MOD)%MOD);
    }
    return f[1];
}
int get_sum(ll x)
{
    if(x<=INF&&1LL*x*x<=n) return g[x];
    //assert(n/(n/x)==x);
    return f[n/x];
}
int main()
{
    int p=sieve(400003);
    scanf("%lld",&n);
    ll sum=0;
    PrimeCount(n);
    int ans=0;
    int tmp=n%MOD;
    for(ll i=2,r;i<=n;i=r+1)
	{
        //[i,r]
		r=n/(n/i);
        if(i<=INF&&i*i<=n)
        {
            for(ll j=i;j<=r;j++)
            {
                if(!is_prime[j]) continue;
                int res1=0,res2=0;
                for(ll x=j;x<=n;x*=j)
                {
                    int t=(n/x)%MOD;
                    add(res1,t),add(res2,1LL*t*t%MOD);
                }
                add(ans,2LL*tmp*j%MOD*res1%MOD);
                dec(ans,2LL*j*res2%MOD);
            }
            continue;
        }
        int x=get_sum(r);
        int cur=(n/i)%MOD;
        dec(x,get_sum(i-1));
        add(ans,2LL*tmp*cur%MOD*x%MOD);
		dec(ans,2LL*cur*cur%MOD*x%MOD);
	}
    printf("%d\n",ans);
    return 0;
}