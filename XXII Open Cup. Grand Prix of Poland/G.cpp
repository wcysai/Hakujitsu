#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 2000005
#define INF 1000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,q;
ll H;
int type[MAXN];
ll val[MAXN];
struct node
{
    ll l,r,val;
};
node id;
int spos[MAXN];
ll calc(node &x,ll pos)
{
    if(pos<x.l) return 0;
    else if(pos<=x.r) return x.val;
    else return x.val+pos-x.r;
}
node construct(int type,ll val)
{
    if(type==1)
    {
        return (node){val+1,val+1,1};
    }
    else if(type==2)
    {
        return (node){val,INF,val};
    }
    else 
    {
        return (node){1,val,val};
    }
}
node comb(node &lhs,node &rhs)
{
    if(lhs.val<rhs.l)
    {
        ll nl=min(INF,rhs.l-lhs.val+lhs.r);
        ll nr=min(INF,nl+(rhs.r-rhs.l));
        assert(nl<=nr);
        ll nval=calc(rhs,calc(lhs,nl));
        return (node){nl,nr,nval};
    }
    else if(lhs.val<=rhs.r)
    {
        ll nl=min(INF,lhs.l);
        ll nr=min(INF,lhs.r+(rhs.r-lhs.val));
        assert(nl<=nr);
        ll nval=calc(rhs,calc(lhs,nl));
        return (node){nl,nr,nval};
    }
    else
    {
        ll nl=lhs.l;
        ll nr=lhs.r;
        assert(nl<=nr);
        ll nval=calc(rhs,calc(lhs,nl));
        return (node){nl,nr,nval};
    }
}
struct segtree
{
    node p[4*MAXN];
    int lb[4*MAXN],rb[4*MAXN];
    void pushup(int k)
    {
        p[k]=comb(p[k*2],p[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        lb[k]=l; rb[k]=r;
        if(l==r)
        {
            spos[l]=k;
            p[k]=construct(type[l],val[l]);
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int pos,int type,ll val)
    {
        if(l==r)
        {
            p[k]=construct(type,val);
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos,type,val); else update(k*2+1,mid+1,r,pos,type,val);
        pushup(k);
    }
    int find_pos(int x)
    {
        int k=spos[x];
        if(p[k].l>H) return -1;
        node cur=p[k];
        while(k>1)
        {
            if(k&1);
            else
            {
                if(comb(cur,p[k+1]).l>H)
                {
                    int now=k+1;
                    while(lb[now]!=rb[now])
                    {
                        if(comb(cur,p[now*2]).l>H)
                        {
                            now=now*2;
                        }
                        else 
                        {
                            cur=comb(cur,p[now*2]);
                            now=now*2+1;
                        }
                    }
                    if(comb(cur,p[now]).l>H) return lb[now]-1; else return lb[now];
                }
                else cur=comb(cur,p[k+1]);
            }
            k=k/2;
        }
        return n;
    }
    node query(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return id;
        if(l>=x&&r<=y) return p[k];
        int mid=(l+r)/2;
        node lhs=query(k*2,l,mid,x,y);
        node rhs=query(k*2+1,mid+1,r,x,y);
        return comb(lhs,rhs);
    }

}seg;
char str[2];
int main()
{
    id=(node){1,1,1};
    ll x,y,z;
    /*while(scanf("%lld%lld%lld",&x,&y,&z)==3) 
    {
        node p=(node){x,y,z};
        node pq=comb(p,id); node qp=comb(id,p);
        assert(pq.l==p.l&&pq.r==p.r&&pq.val==p.val);
        assert(qp.l==p.l&&qp.r==p.r&&qp.val==p.val);
    }*/
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%lld",&n,&q,&H);
        for(int i=1;i<=n;i++)
        {
            scanf("%s",str);
            ll x;
            scanf("%lld",&x);
            if(str[0]=='B') type[i]=1; else if(str[0]=='K') type[i]=2; else type[i]=3;
            val[i]=x; 
        }
        seg.build(1,1,n);
        for(int i=0;i<q;i++)
        {
            scanf("%s",str);
            if(str[0]=='Z')
            {
                int pos; ll x;
                scanf("%d",&pos);
                scanf("%s",str);
                if(str[0]=='B') type[pos]=1; else if(str[0]=='K') type[pos]=2; else type[pos]=3;
                scanf("%lld",&x);
                val[pos]=x;
                seg.update(1,1,n,pos,type[pos],val[pos]);
            }
            else
            {
                int pos;
                scanf("%d",&pos);
                printf("%d\n",seg.find_pos(pos));
            }
        }
    }
    return 0;
}