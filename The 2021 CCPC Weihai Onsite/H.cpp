#include<bits/stdc++.h>
#define MAXN 205
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,w[MAXN],val[MAXN];
int dp[MAXN][MAXN],ndp[MAXN];
/*
dp[i][j]:
maximum benefit
in subtree of i
num of vertices with dist<=j to i inside subtree chosen
*/
vector<int> G[MAXN];
void upd(int &a,int b) {a=max(a,b);}
void dfs(int v,int p)
{
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
    }
    for(int i=-1;i<=n-1;i++) dp[v][i+1]=(i==-1?0:val[i]-w[v]);
    for(auto to:G[v])
    {
        if(to==p) continue;
        for(int i=0;i<=n;i++)
            ndp[i]=-INF;
        for(int i=-1;i<=n-1;i++)
            for(int j=-1;j<=n-1;j++)
                if(j>=i-1&&j-1<=i) upd(ndp[i+1],dp[v][i+1]+dp[to][j+1]);
        swap(dp[v],ndp);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&w[i]);
    for(int i=0;i<=n-1;i++) scanf("%d",&val[i]);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
        for(int j=0;j<=n;j++)
            dp[i][j]=-INF;
    dfs(1,0);
    int ans=0;
    for(int i=-1;i<=n-1;i++) ans=max(ans,dp[1][i+1]);
    printf("%d\n",ans);
    return 0;
}