#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,tot1,tot2;
map<pair<P,int>,int > mp1;
map<P,int> mp2;
set<int> G1[MAXN],G2[MAXN];
bool vis[MAXN];
int get_id(pair<P,int> p)
{
	if(mp1.find(p)==mp1.end()) mp1[p]=++tot1;
	return mp1[p];
}
int get_id(P p)
{
	if(mp2.find(p)==mp2.end()) mp2[p]=++tot2;
	return mp2[p];
}
bool f;
void dfs1(int v,int p)
{
	vis[v]=true;
	for(auto to:G1[v])
	{
		if(to==p||to==v) continue;
		if(vis[to]) f=false;
		else dfs1(to,v);
	}
}
void dfs2(int v,int p)
{
	vis[v]=true;
	for(auto to:G2[v])
	{
		if(to==p||to==v) continue;
		if(vis[to]) f=false;
		else dfs2(to,v);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int a1,b1,c1,a2,b2,c2;
		scanf("%d%d%d%d%d%d",&a1,&b1,&c1,&a2,&b2,&c2);
		int u=get_id(make_pair(P(a1,b1),c1)),v=get_id(make_pair(P(a2,b2),c2));
		G1[u].insert(v); G1[v].insert(u);
		u=get_id(P(a1,b1)); v=get_id(P(a2,b2));
		G2[u].insert(v); G2[v].insert(u);
	}
	f=true;
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=tot1;i++)
		if(!vis[i]) dfs1(i,0);
	if(f) puts("No true closed chains"); else puts("True closed chains");
	f=true;
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=tot2;i++)
		if(!vis[i]) dfs2(i,0);
	if(f) puts("No floor closed chains"); else puts("Floor closed chains");
	return 0;
}