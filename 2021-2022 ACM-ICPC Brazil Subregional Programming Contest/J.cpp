#include<bits/stdc++.h>
#define MAXN 55
#define MAXV 3005
#define MAXE 5005
#define INF 1000000000
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct edge{int to,cap,rev;};
int n,m,k,c,V;
int p[MAXN][MAXN];
vector<edge> G[MAXV];
int level[MAXV];
int iter[MAXV];
void add_edge(int from,int to,int cap)
{
    G[from].push_back((edge){to,cap,(int)G[to].size()});
    G[to].push_back((edge){from,0,(int)G[from].size()-1});
}
void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int> que;
    level[s]=0;
    que.push(s);
    while(!que.empty())
    {
        int v=que.front(); que.pop();
        for(int i=0;i<(int)G[v].size();i++)
        {
            edge &e=G[v][i];
            if(e.cap>0&&level[e.to]<0)
            {
                level[e.to]=level[v]+1;
                que.push(e.to);
            }
        }
    }
}

ll dfs(int v,int t,int f)
{
    if(v==t) return f;
    for(int &i=iter[v];i<(int)G[v].size();i++)
    {
        edge &e=G[v][i];
        if(level[v]<level[e.to]&&e.cap>0)
        {
            ll d=dfs(e.to,t,min(f,e.cap));
            if(d>0)
            {
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}
ll max_flow(int s,int t)
{
    ll flow=0;
    for(;;)
    {
        bfs(s);
        if(level[t]<0) return flow;
        memset(iter,0,sizeof(iter));
        ll f;
        while((f=dfs(s,t,INF))>0)
          flow+=f;
    }
}
int get_id(int x,int y)
{
    return (x-1)*(m+1)+y;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&k,&c);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&p[i][j]);
    V=n*(m+1)+2;
    int s=V-1,t=V;
    for(int i=1;i<=n;i++)
    {
        add_edge(s,get_id(i,1),INF);
        for(int j=1;j<=m;j++) add_edge(get_id(i,j),get_id(i,j+1),INF-p[i][j]);
        add_edge(get_id(i,m+1),t,INF);
    }
    for(int i=0;i<k;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        for(int j=1;j<=m;j++)
        {
            add_edge(get_id(u,j),get_id(v,j),c);
            add_edge(get_id(v,j),get_id(u,j),c);
        }
    }
    printf("%lld\n",1LL*n*INF-max_flow(s,t));
    return 0;
}
