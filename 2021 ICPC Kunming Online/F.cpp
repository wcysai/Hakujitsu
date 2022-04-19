#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
P maxi[MAXN],mini[MAXN];
int maxsum[MAXN],minsum[MAXN];
int maxall[MAXN],minall[MAXN];
vector<int> G[MAXN];
void dfs(int v,int p)
{
	maxi[v]=P(-INF,-INF);
	mini[v]=P(INF,INF); 
	maxall[v]=-INF; minall[v]=INF;
	for(auto to:G[v])
	{
		if(to==p) continue;
		dfs(to,v);
		if(a[to]>maxi[v].F)
		{
			maxi[v].S=maxi[v].F;
			maxi[v].F=a[to];
		}
		else if(a[to]>maxi[v].S) maxi[v].S=a[to];
		if(a[to]<mini[v].F)
		{
			mini[v].S=mini[v].F;
			mini[v].F=a[to];
		}
		else if(a[to]<mini[v].S) mini[v].S=a[to];
		if(maxsum[to]!=-INF) maxall[v]=max(maxall[v],a[v]+maxsum[to]);
		if(minsum[to]!=INF) minall[v]=min(minall[v],a[v]+minsum[to]); 
	}
	maxsum[v]=(maxi[v].F==-INF?-INF:a[v]+maxi[v].F);
	minsum[v]=(mini[v].F==INF?INF:a[v]+mini[v].F);
}
int absi(int x)
{
	return max(-x,x);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=0;i<n-1;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v); G[v].push_back(u);
	}
	dfs(1,0);
	double ans=0.0;
	for(int i=1;i<=n;i++)
	{
		if(maxi[i].F!=-INF&&maxi[i].S!=-INF) ans=max(ans,1.0*absi(a[i]+maxi[i].F+maxi[i].S)/3.0);
		if(mini[i].F!=INF&&mini[i].S!=INF) ans=max(ans,1.0*absi(a[i]+mini[i].F+mini[i].S)/3.0);
		if(maxall[i]!=-INF) ans=max(ans,1.0*absi(maxall[i])/3.0);
		if(minall[i]!=INF) ans=max(ans,1.0*absi(minall[i])/3.0);
		if(maxi[i].F!=-INF) ans=max(ans,1.0*absi(a[i]+maxi[i].F)/2.0);
		if(mini[i].F!=INF) ans=max(ans,1.0*absi(a[i]+mini[i].F)/2.0);
	}
	printf("%.15f\n",ans*ans/4.0);
	return 0;
}