#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<P> G[MAXN];
int n,m,c[MAXN];
int p[MAXN];
ll sum[MAXN],f[MAXN];
struct edge{int u,v,cost;};
bool cmp(const edge &e1,const edge &e2)
{
    return e1.cost>e2.cost;
}
edge es[MAXN];
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        f[i]=INF;
        sum[i]=c[i];
    }
}
int find(int x)
{
    if(p[x]==x) return x;
    else return p[x]=find(p[x]);
}
void unite(int x,int y,ll cost)
{
    x=find(x);
    y=find(y);
    if(x==y) return;
    p[x]=y;
    f[y]=max(min(f[x],min(f[y],cost)-sum[x]),min(f[y],min(f[x],cost)-sum[y]));
    sum[y]=sum[x]+sum[y];
}
bool same(int x,int y)
{
    return find(x)==find(y);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    int tot=0;
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        es[i]=(edge){u,v,w};
    }
    sort(es,es+m,cmp);
    init(n);
    for(int i=0;i<m;i++) 
        unite(es[i].u,es[i].v,es[i].cost);
    ll ans=f[find(1)];
    if(ans<=0) puts("-1"); else printf("%lld\n",ans);
    return 0; 
}