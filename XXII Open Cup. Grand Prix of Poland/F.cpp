#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
int T,n,a[MAXN];
vector<int> pos[MAXN];
int maxi,type[MAXN];
P get(int x,int y)
{
    ll num=x/y,mod=x%y;
    ll res=(num%2==0?1LL*(num/2)*y+mod:1LL*((num+1)/2)*y);
    int par=((num+(mod?1:0))&1);
    return make_pair(res,par);
}
struct segtree
{
    ll sum[4*MAXN];
    P state[4*MAXN];
    void pushup(int k)
    {
        ll res=state[k*2].F+(state[k*2].S?sum[k*2+1]-state[k*2+1].F:state[k*2+1].F);
        int par=(state[k*2].S^state[k*2+1].S);
        state[k]=make_pair(res,par);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            sum[k]=a[l];
            state[k]=get(a[l],1);
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k); 
        sum[k]=sum[k*2]+sum[k*2+1];
    }
    void update(int k,int l,int r,int pos,P p)
    {
        if(l==r)
        {
            state[k]=p;
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos,p); else update(k*2+1,mid+1,r,pos,p);
        pushup(k);
    }
}seg;
int ans[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        maxi=0;
        for(int i=1;i<=n;i++) 
        {
            scanf("%d",&a[i]); maxi=max(maxi,a[i]);
            for(int j=2;j<=a[i];j++) pos[j].push_back(i);
        }
        seg.build(1,1,n);
        printf("%lld\n",seg.state[1].F);
        for(int now=2;now<=maxi;now++)
        {
            for(auto x:pos[now])
            {
                seg.update(1,1,n,x,get(a[x],now));
            }
            printf("%lld\n",seg.state[1].F);
        }
        for(int i=1;i<=maxi;i++) pos[i].clear();
    }
    return 0;
}