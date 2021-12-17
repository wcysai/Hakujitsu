#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
bool vis[MAXN];
void dfs(int v)
{
    vis[v]=true;
    if(!vis[a[v]]) dfs(a[v]);
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    memset(vis,false,sizeof(vis));
    int cnt=0;
    for(int i=1;i<=n;i++)
        if(!vis[i]) {dfs(i); cnt++;}
    int need=n-cnt;
    int mini=max(need-k,(need+k)&1);
    int maxi=min(need+k,n-1-((need+k+(n-1))&1));
    printf("%d %d\n",mini,maxi);
    return 0; 
}