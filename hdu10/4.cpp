#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 10000005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int prime[MAXN];
bool is_prime[MAXN];
int T,cnt[MAXM];
ll n;
int k;
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
int main()
{
    int p=sieve(100);
    int ss=1;
    for(int i=0;i<8;i++) ss=ss*prime[i];
    for(int i=1;i<=ss;i++)
    {
        bool f=true;
        for(int j=0;j<8;j++) if(i%prime[j]==0) f=false;
        cnt[i]=cnt[i-1]; if(f) cnt[i]++;
    }
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%d",&n,&k);
        ll ans=0;
        if(k<=8)
        {
            for(int i=0;i<(1<<k);i++)
            {
                int s=1;
                for(int j=0;j<k;j++) if(i&(1<<j)) s=s*prime[j];
                if(__builtin_popcount(i)&1) ans-=n/s; else ans+=n/s;
            }
        }
        else
        {
            for(int i=0;i<(1<<(k-8));i++)
            {
                ll s=1;
                for(int j=0;j<k-8;j++) if(i&(1<<j)) s=s*prime[j+8];
                ll tmp=n/s;
                ll res=cnt[tmp%ss]+1LL*tmp/ss*cnt[ss];
                if(__builtin_popcount(i)&1) ans-=res; else ans+=res;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}