#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,root;
vector<int> G[MAXN];
int dp[MAXN][2][2];//has a father or not, all even or all odd
void dfs(int v,int p)
{
	if(G[v].size()==1)
	{
		dp[v][0][0]=0; dp[v][0][1]=INF;
		dp[v][1][1]=0; dp[v][1][1]=INF;
		return;
	}
	vector<int> change;
	for(auto to:G[v])
	{
		if(to==p) continue;
		dfs(to,v);
		dp[v][0][0]+=min(1+min(dp[to][0][0],dp[to][0][1]),dp[to][1][1]);
		dp[v][1][0]+=min(1+min(dp[to][0][0],dp[to][0][1]),dp[to][1][1]);
		dp[v][0][1]+=1+min(dp[to][0][0],dp[to][0][1]);
		dp[v][1][1]+=1+min(dp[to][0][0],dp[to][0][1]);
		change.push_back(dp[to][1][0]-(1+min(dp[to][0][0],dp[to][0][1])));
	}
	sort(change.begin(),change.end());
	dp[v][1][1]+=change[0];
	for(int i=1;i<(int)change.size();i++) if(change[i]<0) dp[v][1][1]+=change[i]; else break;
	if(change.size()==1) dp[v][0][1]=INF;
	else
	{
		dp[v][0][1]+=change[0]; dp[v][0][1]+=change[1];
		for(int i=2;i<(int)change.size();i++) if(change[i]<0) dp[v][0][1]+=change[i]; else break;
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
	if(n==1)
	{
		puts("0");
		return 0;
	}
	else if(n==2)
	{
		puts("1");
		return 0;
	}
	root=1;
	for(int i=1;i<=n;i++) if((int)G[i].size()>=2) root=i;
	dfs(root,0);
	printf("%d\n",min(dp[root][0][1],dp[root][0][0]));
	return 0;
}