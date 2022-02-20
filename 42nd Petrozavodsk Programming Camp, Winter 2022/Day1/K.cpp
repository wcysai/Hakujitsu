#include<bits/stdc++.h>
#define MAXN 23
#define MAXM 505
#define INF 1000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
int n,m;
bool forbid[MAXN][3];
int c[MAXN];
vector<P> G[MAXN];
string str;
vector<P> st_color(int v,int col)
{
	vector<P> tmp;
	for(auto p:G[v])
	{
		if(p.S/3!=col) continue;
		if(c[p.F]!=-1) continue;
		if(forbid[p.F][p.S%3]) continue;
		forbid[p.F][p.S%3]=true;
		tmp.push_back(P(p.F,p.S%3));
	}
	return tmp;
}
ll solve(vector<int> &v)
{
	//end
	if(v.size()==1)
	{
		int cnt=0;
		for(int i=0;i<3;i++) if(!forbid[v[0]][i]) cnt++;
		return cnt;
	}
	//prune
	for(auto x:v)
	{
		int cnt=0,id=-1;
		for(int i=0;i<3;i++) if(!forbid[x][i]) cnt++,id=i;
		if(cnt==0) return 0;
		if(cnt==1)
		{
			c[x]=id;
			auto tmp=st_color(x,id);
			vector<int> nv;
			for(auto y:v) if(y!=x) nv.push_back(y);
			ll res=solve(nv);
			for(auto p:tmp) forbid[p.F][p.S]=false;
			c[x]=-1;
			return res; 
		}
	}
	//connected components
	bool vis[MAXN],inner[MAXN];
	memset(vis,false,sizeof(vis));
	memset(inner,false,sizeof(inner));
	for(auto x:v) inner[x]=true;
	queue<int> que;
	que.push(v[0]);
	vis[v[0]]=true;
	vector<int> tmp;
	tmp.push_back(v[0]);
	while(que.size())
	{
		int x=que.front(); que.pop();
		for(auto p:G[x]) if(inner[p.F]&&!vis[p.F]) {que.push(p.F); vis[p.F]=true; tmp.push_back(p.F);}
	}
	if(tmp.size()!=v.size())
	{
		ll res=solve(tmp);
		for(auto x:v)
		{
			if(!vis[x])
			{
				tmp.clear();
				que.push(x);
				vis[x]=true; tmp.push_back(x);
				while(que.size())
				{
					int x=que.front(); que.pop();
					for(auto p:G[x]) if(inner[p.F]&&!vis[p.F]) {que.push(p.F); vis[p.F]=true; tmp.push_back(p.F);}
				}
				res=res*solve(tmp);
			}
		}
		return res;
	}
	random_shuffle(v.begin(),v.end());
	P p=P(0,v[0]);
	for(auto x:v)
	{
		int cnt=0;
		for(auto p:G[x])
		{
			if(c[p.F]==-1) continue;
			if(forbid[x][p.S/3]) continue;
			if(forbid[p.F][p.S%3]) continue;
			cnt++;
		}
		p=max(p,P(cnt,x));
	}
	ll res=0;
	int x=p.S;
	for(int i=0;i<3;i++)
	{
		if(forbid[x][i]) continue;
		c[x]=i;
		auto tmp=st_color(x,i);
		vector<int> nv;
		for(auto y:v) if(y!=x) nv.push_back(y);
		res+=solve(nv);
		for(auto p:tmp) forbid[p.F][p.S]=false;
		c[x]=-1;
	}
	return res;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int u,v,x,y;
		scanf("%d",&u);
		cin>>str; x=(str[0]=='R'?0:(str[0]=='G'?1:2));
		scanf("%d",&v);
		cin>>str; y=(str[0]=='R'?0:(str[0]=='G'?1:2));
		G[u].push_back(P(v,x*3+y));
		G[v].push_back(P(u,y*3+x));
	}
	vector<int> v;
	for(int i=1;i<=n;i++) v.push_back(i);
	memset(forbid,false,sizeof(forbid));
	memset(c,-1,sizeof(c));
	printf("%lld\n",solve(v));
	return 0;
}