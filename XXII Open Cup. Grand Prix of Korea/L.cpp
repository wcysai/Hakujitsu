#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 4005
#define MAXM 8005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
struct edge{int to,cap; ll cost; int rev,id;};
int n,m,k;
int V,prevv[MAXN],preve[MAXN];
ll dist[MAXN],h[MAXN];
int u[MAXM],v[MAXM];
ll w[MAXM];
bool inque[MAXN];
vector<edge> G[MAXN];
ll ans[MAXM];
void add_edge(int from,int to,int cap,ll cost,int id)
{
    G[from].push_back((edge){to,cap,cost,(int)G[to].size(),id});
    G[to].push_back((edge){from,0,-cost,(int)G[from].size()-1,0});
}
void dijkstra(int s)
{
    priority_queue<P,vector<P>,greater<P> >que;
    fill(dist+1,dist+V+1,INF);
    dist[s]=0;
    que.push(P(0,s));
    while(!que.empty())
    {
        P p=que.top(); que.pop();
        int v=p.second;
        if(dist[v]<p.first) continue;
        for(int i=0;i<G[v].size();i++)
        {
            edge &e=G[v][i];
            if(e.cap>0&&dist[e.to]>dist[v]+e.cost+h[v]-h[e.to])
            {
                dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
                prevv[e.to]=v;
                preve[e.to]=i;
                que.push(P(dist[e.to],e.to));
            }
        }
    }
}
void spfa(int s)
{
    queue<int>que;
    fill(h+1,h+V+1,INF);
    fill(inque+1,inque+V+1,false);
    h[s]=0;
    que.push(s);
    while(!que.empty())
    {
        int u=que.front(); que.pop();
        for(int i=0;i<(int)G[u].size();i++)
        {
            if(G[u][i].cap>0&&h[u]+G[u][i].cost<h[G[u][i].to])
            {
                h[G[u][i].to]=h[u]+G[u][i].cost;
                prevv[G[u][i].to]=u;
                preve[G[u][i].to]=i;
                if(!inque[G[u][i].to])
                {
                    inque[G[u][i].to]=true;
                    que.push(G[u][i].to);
                }
            }
        }
        inque[u]=false;
    }
}
ll min_cost_flow(int s,int t)
{
    ll res=0;
    spfa(s);
    while(true)
    {
        dijkstra(s);
        if(dist[t]==INF) return res;
        if(h[t]+dist[t]>=0) return res;
        if(prevv[t]==s) return res;
        for(int v=1;v<=V;v++) h[v]+=dist[v];
        int d=V;
        for(int v=t;v!=s;v=prevv[v])
        {
            d=min(d,G[prevv[v]][preve[v]].cap);
        }
        res+=d*h[t];
        for(int v=t;v!=s;v=prevv[v])
        {
            edge &e=G[prevv[v]][preve[v]];
            e.cap-=d;
            G[v][e.rev].cap+=d;
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    V=n+m+2;
    int s=V-1,t=V;
    for(int i=1;i<=k;i++)
    {
        scanf("%d%d%lld",&u[i],&v[i],&w[i]);
        add_edge(u[i],n+v[i],1,-w[i],i);
    }
    for(int i=1;i<=n;i++) add_edge(s,i,1,0,-1);
    for(int i=1;i<=m;i++) add_edge(n+i,t,1,0,-1);
    min_cost_flow(s,t);
    add_edge(t,s,1,0,-1);
    add_edge(s,t,1,0,-1);
    for(int i=1;i<=n;i++)
        for(auto e:G[i])
            if(e.to>=n+1&&e.to<=n+m&&e.cap==0)
            {
                dijkstra(i);
                ans[e.id]=-e.cost+dist[e.to]+h[e.to]-h[i];
            }
    for(int i=1;i<=k;i++) printf("%lld\n",ans[i]);
    return 0;
}