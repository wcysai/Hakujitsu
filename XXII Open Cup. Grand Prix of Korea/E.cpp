#include<bits/stdc++.h>
#define MAXN 65
#define MAXK 1005
#define INF 4000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef pair<int,int> P;
typedef long long ll;
int n,k;
ll p;
int dp[MAXN][MAXK];
int tmp[MAXK];
ll c[MAXN],w[MAXN];
vector<ll> val[MAXN];
vector<ll> comb_max(vector<ll> &a,vector<ll> &b)
{
    vector<ll> c(k+1);
    for(int i=0;i<=k;i++) c[i]=-INF;
    for(int i=0;i<=k;i++)
        for(int j=0;j<=i;j++)
            c[i]=max(c[i],a[j]+b[i-j]);
    return c;
}
vector<ll> get_pow_max(vector<ll> a,ll x)
{
    vector<ll> b(k+1);
    for(int i=0;i<=k;i++) b[i]=(i==0?0:-INF);
    while(x)
    {
        if(x&1) b=comb_max(b,a);
        a=comb_max(a,a);
        x>>=1;
    }
    return b;
}
vector<ll> comb_min(vector<ll> &a,vector<ll> &b)
{
    vector<ll> c(k+1);
    for(int i=0;i<=k;i++) c[i]=INF;
    for(int i=0;i<=k;i++)
        for(int j=0;j<=i;j++)
            c[i]=min(c[i],a[j]+b[i-j]);
    return c;
}
vector<ll> get_pow_min(vector<ll> a,ll x)
{
    vector<ll> b(k+1);
    for(int i=0;i<=k;i++) b[i]=(i==0?0:INF);
    while(x)
    {
        if(x&1) b=comb_min(b,a);
        a=comb_min(a,a);
        x>>=1;
    }
    return b;
}
int main()
{
    ll maxans,minans;
    scanf("%d%d%lld",&n,&k,&p);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&c[i],&w[i]);
    if(p%c[1]) {puts("-1"); return 0;}
    for(int i=1;i<=n;i++) val[i].resize(k+1);
    for(int i=0;i<=k;i++) val[1][i]=(i==1?w[1]:INF);
    for(int i=2;i<=n;i++)
    {
        val[i]=get_pow_min(val[i-1],c[i]/c[i-1]);
        vector<ll> tmp(k+1);
        val[i][1]=min(val[i][1],w[i]);
    } 
    vector<ll> ans(k+1);
    ans[0]=0;
    for(int i=1;i<=k;i++) ans[i]=INF;
    ll tmpp=p;
    for(int i=n;i>=1;i--)
    {
        if(!p) break;
        ll cnt=p/c[i];
        vector<ll> tmp=get_pow_min(val[i],cnt);
        ans=comb_min(ans,tmp); 
        p-=c[i]*cnt;
    }
    p=tmpp;
    if(ans[k]==INF) {puts("-1"); return 0;} else minans=ans[k];
    for(int i=1;i<=n;i++) val[i].resize(k+1);
    for(int i=0;i<=k;i++) val[1][i]=(i==1?w[1]:-INF);
    for(int i=2;i<=n;i++)
    {
        val[i]=get_pow_max(val[i-1],c[i]/c[i-1]);
        vector<ll> tmp(k+1);
        val[i][1]=max(val[i][1],w[i]);
    } 
    ans[0]=0;
    for(int i=1;i<=k;i++) ans[i]=-INF;
    for(int i=n;i>=1;i--)
    {
        if(!p) break;
        ll cnt=p/c[i];
        vector<ll> tmp=get_pow_max(val[i],cnt);
        ans=comb_max(ans,tmp); 
        p-=c[i]*cnt;
    }
    if(ans[k]==-INF) {puts("-1"); return 0;} else maxans=ans[k];
    printf("%lld %lld\n",minans,maxans);
    return 0;
}