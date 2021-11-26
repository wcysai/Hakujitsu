#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,tot,t,bcc_cnt,mcnt;
vector<int> G[MAXN],bcc[MAXN];
int U[MAXM],V[MAXM],W[MAXM],ecnt[MAXN];
int st[MAXN],dfn[MAXN],low[MAXN],bccno[MAXN];
int sz[MAXN],mini;
bool isbridge[MAXM];
vector<int> tree[MAXN];
void add_edge(int u,int v,int w)
{
    U[++mcnt]=u;V[mcnt]=v;W[mcnt]=w;
    G[u].push_back(mcnt); G[v].push_back(mcnt);
}
int adj(int u,int e)
{
    return U[e]==u?V[e]:U[e];
}
void dfs1(int v,int edge)
{
    dfn[v]=low[v]=++tot;
    st[t++]=v;
    for(auto e:G[v])
    {
        if(e==edge) continue;
        int to=adj(v,e);
        if(!dfn[to])
        {
            dfs1(to,e);
            low[v]=min(low[v],low[to]);
        }
        else low[v]=min(low[v],dfn[to]);
    }
    if(low[v]==dfn[v]&&edge!=-1) isbridge[edge]=true;
}
void dfs2(int v)
{
    dfn[v]=1;
    bccno[v]=bcc_cnt;
    bcc[bcc_cnt].push_back(v);
    for(auto e:G[v])
    {
        int to=adj(v,e);
        if(isbridge[e]) continue;
        if(!dfn[to]) dfs2(to);
    }
}
int tarjan()
{
    bcc_cnt=tot=0;
    memset(dfn,0,sizeof(dfn));
    memset(isbridge,false,sizeof(isbridge));
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs1(i,-1);
    memset(dfn,0,sizeof(dfn));
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])
        {
            bcc_cnt++;
            dfs2(i);
        }
    }
    return bcc_cnt;
}
map<P,int> mp;
void build_bridge_tree()
{
    tarjan();
    for(int i=1;i<=mcnt;i++)
    {
        if(isbridge[i])
        {
            int u=bccno[U[i]],v=bccno[V[i]];
            tree[u].push_back(v); tree[v].push_back(u);
            if(u>v) swap(u,v);
            mp[P(u,v)]=W[i];
        }
        else 
        {
            ecnt[bccno[U[i]]]++;
            mini=min(mini,W[i]);
        }
    }
}
void dfs3(int v,int p)
{
    sz[v]=ecnt[v];
    for(auto to:tree[v])
    {
        if(to==p) continue;
        dfs3(to,v);
        sz[v]+=sz[to]+1;
    }
    if(sz[v]%2==0&&p!=0) mini=min(mini,mp[P(min(p,v),max(p,v))]);
}
int main()
{
    scanf("%d%d",&n,&m);
    ll sum=0;
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w);
        sum+=w;
    }
    if(m%2==0) {printf("%lld\n",sum); return 0;}
    mini=INF+1;
    build_bridge_tree();
    dfs3(1,0);
    printf("%lld\n",sum-mini);
    return 0;
}