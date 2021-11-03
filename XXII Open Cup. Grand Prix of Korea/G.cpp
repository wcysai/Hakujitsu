#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
typedef pair<P,P> PP;
int n,q,a[MAXN];
PP merge(PP &x,PP &y)
{
    PP q;
    q.S.S=x.S.S+y.S.S;
    q.F.F=min(x.F.F,x.S.S+y.F.F);
    q.F.S=min(y.F.S,y.S.S+x.F.S);
    q.S.F=min(min(x.S.F,y.S.F),x.F.S+y.F.F);
    return q;
}
struct segtree
{
    ll lmin[4*MAXN],rmin[4*MAXN],minn[4*MAXN],sum[4*MAXN];
    void pushup(int k)
    {
        sum[k]=sum[k*2]+sum[k*2+1];
        lmin[k]=min(lmin[k*2],sum[k*2]+lmin[k*2+1]);
        rmin[k]=min(rmin[k*2+1],sum[k*2+1]+rmin[k*2]);
        minn[k]=min(min(minn[k*2],minn[k*2+1]),rmin[k*2]+lmin[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            lmin[k]=rmin[k]=minn[k]=min(0,a[l]);
            sum[k]=a[l];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int p,int v)
    {
        if(l==r)
        {
            lmin[k]=rmin[k]=minn[k]=min(0,v);
            sum[k]=v;
            return;
        }
        int mid=(l+r)/2;
        if(p<=mid) update(k*2,l,mid,p,v); else update(k*2+1,mid+1,r,p,v);
        pushup(k);
    }
    PP query(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return PP(P(INF,INF),P(INF,0));
        if(l>=x&&r<=y) return PP(P(lmin[k],rmin[k]),P(minn[k],sum[k]));
        int mid=(l+r)/2;
        PP p=query(k*2,l,mid,x,y);
        PP q=query(k*2+1,mid+1,r,x,y);
        return merge(p,q);
    }
}seg;
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    seg.build(1,1,n);
    for(int i=0;i<q;i++)
    {
        int type,l,r,x;
        scanf("%d",&type);
        if(type==1)
        {
            scanf("%d%d%d",&l,&r,&x);
            int threshold=(x+9)/10;
            bool dead=false;
            ll res=seg.query(1,1,n,1,l-1).S.F;
            if(res+x<=0) dead=true;
            ll dmg=seg.query(1,1,n,1,l-1).F.S;
            PP tmp=seg.query(1,1,n,l,r);
            PP tt=PP(P(dmg,dmg),P(dmg,dmg));
            tmp=merge(tt,tmp);
            res=tmp.S.F;
            if(res+x<=threshold) dmg=threshold-x; else dmg=tmp.F.S;
            dmg=min(dmg,0LL);
            tmp=seg.query(1,1,n,r+1,n);
            tt=PP(P(dmg,dmg),P(dmg,dmg));
            tmp=merge(tt,tmp);
            res=tmp.S.F;
            if(res+x<=0) dead=true; 
            if(dead) puts("0"); else printf("%lld\n",x+tmp.F.S);
        }
        else
        {
            scanf("%d%d",&l,&r);
            seg.update(1,1,n,l,r);
            a[l]=r;
        }
    }
}