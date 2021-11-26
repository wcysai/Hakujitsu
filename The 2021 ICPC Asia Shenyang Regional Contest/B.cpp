#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
bool vis[MAXN];
int res[MAXN],num;
vector<P> G[MAXN];
int cnt[30];
bool flag;
void dfs(int v)
{
    vis[v]=true;
    num++;
    for(int i=0;i<30;i++) cnt[i]+=((res[v]&(1<<i))?1:0);
    for(auto e:G[v])
    {
        int to=e.F,w=e.S;
        if(vis[to]&&((w^res[v])!=res[to])) {flag=false; return;}
        if(vis[to]) continue;
        res[to]=res[v]^w;
        dfs(to);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        G[u].push_back(P(v,w)); G[v].push_back(P(u,w));
    }
    memset(vis,false,sizeof(vis));
    flag=true;
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            num=0; res[i]=0; memset(cnt,0,sizeof(cnt));
            dfs(i);
            if(!flag) {puts("-1"); return 0;}
            for(int j=0;j<30;j++) ans+=1LL*min(cnt[j],num-cnt[j])*(1<<j);
        }
    }
    printf("%lld\n",ans);
    return 0;
}