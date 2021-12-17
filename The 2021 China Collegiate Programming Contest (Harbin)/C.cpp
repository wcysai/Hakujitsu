#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,p[MAXN],c[MAXN];
int dp[MAXN],sz[MAXN],wson[MAXN];
vector<int> G[MAXN];
map<int,int> mp[MAXN];
int occ;
void dfs(int v)
{
    sz[v]=1;
    if(!G[v].size()) return;
    int mx=-1; wson[v]=-1;
    for(auto to:G[v])
    {
        dfs(to); sz[v]+=sz[to];
        if(sz[to]>mx) {mx=sz[to]; wson[v]=to;}
    }
}
void dfs2(int v)
{
    if(!G[v].size())
    {
        mp[v][c[v]]++;
        dp[v]=1;
        return;
    }
    set<int> newly; int tmpocc=occ;
    int sum=0;
    
    dfs2(wson[v]); sum+=dp[wson[v]];
    swap(mp[v],mp[wson[v]]);
    int occ=1;
    for(auto to:G[v])
    {
        if(to==wson[v]) continue;
        dfs2(to); sum+=dp[to];
        for(auto p:mp[to])
        {
            mp[v][p.F]+=p.S;
            if(mp[v][p.F]>occ)
            {
                occ=mp[v][p.F];
                newly.clear(); newly.insert(p.F);
            }
            else if(mp[v][p.F]==occ) newly.insert(p.F);
        } 
    }
    dp[v]=sum-(occ-1);
    if(occ>1)
    {
        mp[v].clear();
        for(auto x:newly) mp[v][x]=1;
    }
    else for(auto x:newly) mp[v][x]=1;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;i++) 
    {
        scanf("%d",&p[i]);
        G[p[i]].push_back(i+1);
    }
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    dfs(1);
    dfs2(1);
    printf("%d\n",dp[1]);
    return 0;
}