#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
vector<P> G[MAXN];
P maxi1[MAXN],maxi2[MAXN];
bool marked[MAXN];
int fa[MAXN];
pair<int,P> ans;
void dfs(int v,int p)
{
	maxi1[v]=P(0,v),maxi2[v]=P(-1,-1);
	for(auto e:G[v])
	{
		int to=e.F,cost=e.S;
		if(to==p) continue;
		dfs(to,v);
		if(marked[v]&&marked[to]) cost=-cost;
		if(maxi1[to].F+cost>maxi1[v].F)
		{
			maxi2[v]=maxi1[v];
			maxi1[v]=maxi1[to]; maxi1[v].F+=cost;
		}
		else if(maxi1[to].F+cost>maxi2[v].F)
		{
			maxi2[v]=maxi1[to]; maxi2[v].F+=cost;
		}
	}
	ans=max(ans,make_pair(maxi1[v].F,P(v,maxi1[v].S)));
	if(maxi2[v].F!=-1) ans=max(ans,make_pair(maxi1[v].F+maxi2[v].F,P(maxi2[v].S,maxi1[v].S)));
}
void dfs2(int v,int p)
{
	fa[v]=p;
	for(auto e:G[v])
	{
		int to=e.F,cost=e.S;
		if(to==p) continue;
		dfs2(to,v);
	}
}
int main()
{
	scanf("%d",&n);
	int sum=0;
	for(int i=0;i<n-1;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w); sum+=w;
		G[u].push_back(P(v,w)); G[v].push_back(P(u,w));
	}
	sum*=2;
	ans=make_pair(0,P(INF,INF));
	dfs(1,0);
	sum-=ans.F;
	dfs2(ans.S.F,0);
	int now=ans.S.S;
	while(now)
	{
		marked[now]=true;
		now=fa[now];
	}
	ans=make_pair(0,P(INF,INF));
	dfs(1,0);
	sum-=ans.F;
	printf("%d\n",sum);
	return 0;
}