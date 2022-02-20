#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
int N,M,K;
vector<int> G[MAXN];
int type[MAXN];
int deg[MAXN];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&M,&K);
		for(int i=1;i<=N;i++) type[i]=-1;
		for(int i=1;i<=N;i++) G[i].clear();
		for(int i=0;i<M;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			G[u].push_back(v); G[v].push_back(u);
		}
		for(int i=1;i<=N;i++)
		{
			int cnt0=0,cnt1=0;
			for(auto to:G[i])
			{
				if(type[to]==0) cnt0++;
				else if(type[to]==1) cnt1++;
			}
			if(cnt0>cnt1) type[i]=1; else type[i]=0;
		}
		queue<int> que;
		for(int i=1;i<=N;i++)
		{
			deg[i]=0;
			if(type[i]==-1) continue;
			for(auto to:G[i])
			{
				if(type[to]!=-1&&(type[to]^type[i])) deg[i]++;
			}
			if(deg[i]<K+1) que.push(i);
		}
		while(que.size())
		{
			int v=que.front(); que.pop();
			for(auto to:G[v])
			{
				if(type[to]!=-1&&(type[to]^type[v])) 
				{
					deg[to]--;
					if(deg[to]==K) que.push(to);
				}
			}
			type[v]=-1;
		}
		vector<int> R,B;
		for(int i=1;i<=N;i++) if(type[i]==0) R.push_back(i); else if(type[i]==1) B.push_back(i);
		printf("%d",(int)R.size());
		for(auto x:R) printf(" %d",x);
		puts("");
		printf("%d",(int)B.size());
		for(auto x:B) printf(" %d",x);
		puts("");
	}
	return 0;
}