#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,a[MAXN];
struct segtree
{
    int len[4*MAXN];
    ll maxi[4*MAXN],mini[4*MAXN],sum[4*MAXN];
    ll addv[4*MAXN],setv[4*MAXN];
    void pushup(int k)
    {
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
        mini[k]=min(mini[k*2],mini[k*2+1]);
        sum[k]=sum[k*2]+sum[k*2+1];
    }
    void st(int k,ll val) 
    {
        setv[k]=val; addv[k]=0; maxi[k]=mini[k]=val; sum[k]=len[k]*val;  
    }
    void add(int k,ll val)
    {
        addv[k]+=val; maxi[k]+=val; mini[k]+=val; sum[k]+=len[k]*val;
    }
    void pushdown(int k)
    {
        if(setv[k]!=-1)
        {
            for(int i=k*2;i<=k*2+1;i++) st(i,setv[k]);
            setv[k]=-1;
        }
        if(addv[k]!=0)
        {
            for(int i=k*2;i<=k*2+1;i++) add(i,addv[k]);
            addv[k]=0;
        }
    }
    void build(int k,int l,int r)
    {
        len[k]=r-l+1; addv[k]=0; setv[k]=-1;
        if(l==r)
        {
            mini[k]=maxi[k]=sum[k]=a[l];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update_add(int k,int l,int r,int x,int y,int val)
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y)
        {
            add(k,val);
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        update_add(k*2,l,mid,x,y,val); update_add(k*2+1,mid+1,r,x,y,val);
        pushup(k);
    }
    void update_sqrt(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y&&maxi[k]-mini[k]<=1)
        {
            int ub=(int)sqrt(maxi[k]),lb;
            if(1LL*ub*ub==maxi[k]) lb=ub-1; else lb=ub;
            if(lb==ub) st(k,lb);
            else add(k,ub-maxi[k]);
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        update_sqrt(k*2,l,mid,x,y); update_sqrt(k*2+1,mid+1,r,x,y);
        pushup(k);
    }
    ll query_sum(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return 0;
        if(l>=x&&r<=y) return sum[k];
        pushdown(k);
        int mid=(l+r)/2;
        return query_sum(k*2,l,mid,x,y)+query_sum(k*2+1,mid+1,r,x,y);
    }
}seg;
int main()
{
    //freopen("H.in","r",stdin);
    //clock_t startTime,endTime;
    //startTime = clock();
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    seg.build(1,1,n);
    ll ans=0;
    for(int i=0;i<q;i++)
    {
        int type,l,r,x;
        scanf("%d%d%d",&type,&l,&r);
        if(type==1)
        {
            scanf("%d",&x);
            seg.update_add(1,1,n,l,r,x);
        }
        else if(type==2) seg.update_sqrt(1,1,n,l,r);
        else 
        {
            printf("%lld\n",seg.query_sum(1,1,n,l,r));
            //ans+=seg.query_sum(1,1,n,l,r);
        }
    }
    //printf("%lld\n",ans);
    //endTime = clock();//计时结束
    //cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}