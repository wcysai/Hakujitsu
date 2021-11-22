#include<bits/stdc++.h>
#define MAXN 250005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],dep[MAXN],cnt[MAXN],fa[MAXN];
vector<int> G[MAXN];
vector<int> v;
void dfs(int v,int p,int d,int f,int need)
{
    dep[v]=d; fa[v]=f; 
    if(dep[v]==need) cnt[f]++;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v,d+1,f,need);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++) 
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    int mini=INF;
    for(int i=1;i<=n;i++) {scanf("%d",&a[i]); mini=min(mini,a[i]);}
    for(int i=1;i<=n;i++) if(mini==a[i]) v.push_back(i);
    assert((int)v.size()<=2);
    if(v.size()==1)
    {
        for(auto to:G[v[0]]) dfs(to,v[0],1,to,a[v[0]]);
        vector<P> endpoints;
        vector<int> inner,others;
        for(int i=1;i<=n;i++) 
        {
            if(dep[i]==a[v[0]]) endpoints.push_back(P(cnt[fa[i]],i));
            else if(dep[i]<a[v[0]]) inner.push_back(i);
            else others.push_back(i);
        }
        sort(endpoints.begin(),endpoints.end());
        for(auto x:endpoints) printf("%d ",x.S);
        for(auto x:inner) printf("%d ",x);
        for(auto x:others) printf("%d ",x);
    }
    else
    {
        dfs(v[0],v[1],1,v[0],a[v[0]]); dfs(v[1],v[0],1,v[1],a[v[0]]);
       vector<P> endpoints;
        vector<int> inner,others;
        for(int i=1;i<=n;i++) 
        {
            if(dep[i]==a[v[0]]) endpoints.push_back(P(cnt[fa[i]],i));
            else if(dep[i]<a[v[0]]) inner.push_back(i);
            else others.push_back(i);
        }
        sort(endpoints.begin(),endpoints.end());
        for(auto x:endpoints) printf("%d ",x.S);
        for(auto x:inner) printf("%d ",x);
        for(auto x:others) printf("%d ",x);
    }
    return 0;
}