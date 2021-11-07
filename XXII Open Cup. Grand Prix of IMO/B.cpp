#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,K,w,q,a[MAXN],inv;
int comb[10][10];
int p[MAXN][10];
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
struct segtree
{
    int sz[4*MAXN],sum1[6][4*MAXN],sum2[6][4*MAXN];
    void pushup(int k)
    {
        sz[k]=sz[k*2]+sz[k*2+1];
        //compute \sum bi*i^j
        for(int pw=0;pw<=K;pw++)
        {
            sum1[pw][k]=sum1[pw][k*2];
            for(int i=0;i<=pw;i++) add(sum1[pw][k],1LL*p[sz[k*2]][pw-i]*comb[pw][i]%MOD*sum1[i][k*2+1]%MOD);
        }
        for(int shift=0;shift<=w;shift++)
        {
            sum2[shift][k]=sum2[shift][k*2];
            int nshift=(shift+sz[k*2])%w;
            add(sum2[shift][k],sum2[nshift][k*2+1]);
        }
    }
    void update(int k,int l,int r,int pos,int delta)
    {
        if(l==r)
        {
            if(delta==1)
            {
                sz[k]++;
                for(int pw=0;pw<=K;pw++) add(sum1[pw][k],1LL*(l-1)*p[sz[k]][pw]%MOD);
                for(int shift=0;shift<=w;shift++)
                {
                    int nshift=(shift+sz[k]-1)%w;
                    add(sum2[shift][k],1LL*p[(nshift+1)%w][K]*(l-1)%w);
                }
            }
            else
            {
                for(int pw=0;pw<=K;pw++) dec(sum1[pw][k],1LL*(l-1)*p[sz[k]][pw]%MOD);
                for(int shift=0;shift<=w;shift++)
                {
                    int nshift=(shift+sz[k]-1)%w;
                    dec(sum2[shift][k],1LL*p[(nshift+1)%w][K]*(l-1)%w);
                }
                sz[k]--;
            }
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos,delta); else update(k*2+1,mid+1,r,pos,delta);
        pushup(k);
    }
    int query()
    {
        int ret=sum1[K][1];
        dec(ret,sum2[0][1]);
        ret=1LL*ret*inv%MOD;
        return ret;
    }
}seg;
int main()
{
    for(int i=0;i<=100001;i++)
    {
        p[i][0]=1;
        for(int j=1;j<=9;j++) p[i][j]=1LL*p[i][j-1]*i%MOD;
    }
    comb[0][0]=1;
    for(int i=1;i<=9;i++)
    {
        comb[i][0]=comb[i][i]=1;
        for(int j=1;j<i;j++) 
        {
            comb[i][j]=comb[i-1][j];
            add(comb[i][j],comb[i-1][j-1]);
        }
    }
    scanf("%d%d%d",&n,&K,&w);
    inv=pow_mod(w,MOD-2);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&a[i]);
        seg.update(1,1,100001,a[i]+1,1);
    }
    scanf("%d",&q);
    for(int i=0;i<q;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        seg.update(1,1,100001,a[x]+1,-1);
        a[x]=y;
        seg.update(1,1,100001,a[x]+1,1);
        printf("%d\n",seg.query());
    }
    return 0;
}