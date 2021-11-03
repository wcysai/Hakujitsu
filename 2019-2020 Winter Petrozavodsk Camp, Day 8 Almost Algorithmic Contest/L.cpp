#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 2000000000000000000LL
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
ll C;
ll val[MAXN],a[MAXN],sum[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
ll get_res(ll x)
{
    if(x==0) return INF;
    ll l=0,r=C/x+1;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(1LL*min(x,mid)<=C/x/mid) l=mid; else r=mid;
    }
    return l;
}
ll calc_ans(ll x,ll y)
{
    if(x>y) swap(x,y);
    assert(x<=1000000);
    assert(y!=INF);
    int pos;
    int l=0,r=1000001;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(val[mid]>=y) l=mid; else r=mid;
    }
    pos=l;
    ll res;
    if(pos>=x) res=1LL*((y+1)%MOD)*(x+1)%MOD; else res=(sum[x]-sum[pos]+1LL*(y+1)%MOD*(pos+1)%MOD)%MOD;
    if(res<0) res+=MOD;
    return res;
}
int main()
{
    scanf("%d%lld",&n,&C);
    for(int i=1;i<=1000000;i++) 
    {
        val[i]=get_res(i)+1;
        sum[i]=sum[i-1]+val[i];
    }
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    int ans=1;
    for(int i=1;i<=n-1;i++)
    {
        if(a[i]==0||a[i+1]==0) continue;
        if(a[i]!=-1&&a[i+1]!=-1&&min(a[i],a[i+1])>C/a[i]/a[i+1])
        {
            puts("0");
            return 0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(a[i]==-1&&(i==1||a[i-1]==-1||a[i-1]==0)&&(i==n||a[i+1]==-1||a[i+1]==0))
        {
            puts("-1");
            return 0;
        }
    }
    int now=1;
    while(now<=n)
    {
        while(now<=n&&a[now]!=-1) now++;
        if(now>n) break;
        if(a[now+1]==-1)
        {
            ll x=(now==1?INF:get_res(a[now-1]));
            ll y=(now+1==n?INF:get_res(a[now+2]));
            ll res=calc_ans(min(1000000LL,x),y)+calc_ans(x,min(1000000LL,y))-calc_ans(min(1000000LL,x),min(1000000LL,y));
            res=res%MOD;
            if(res<0) res+=MOD;
            ans=1LL*ans*res%MOD;
            now+=2;
        }
        else
        {
            ll x=(now==1?INF:get_res(a[now-1]));
            ll y=(now==n?INF:get_res(a[now+1]));
            ans=1LL*ans*((min(x,y)+1)%MOD)%MOD;
            now++;
        }
    }
    printf("%d\n",ans);
    return 0;
}