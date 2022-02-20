#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000001
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k,t[MAXN];
vector<int> G[MAXN];
int d[MAXN];
int ds[MAXN],dt[MAXN];
bool good[MAXN];
int nd[MAXN];
void dijkstra(int s)
{
    priority_queue<P,vector<P>,greater<P> > que;
    fill(d+1,d+n+1,INF);
    d[s]=t[s];
    que.push(P(0,s));
    while(!que.empty())
    {
        P p=que.top(); que.pop();
        int v=p.second;
        if(d[v]<p.first) continue;
        for(auto to:G[v])
        {
            if(d[to]>d[v]+t[to])
            {
                d[to]=d[v]+t[to];
                que.push(P(d[to],to));
            }
        }
    }
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%d",&t[i]);
	bool dir=false;
	for(int i=0;i<m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		if(u==1&&v==n) dir=true;
		if(u==n&&v==1) dir=true;
		G[u].push_back(v); G[v].push_back(u);
	}
	if(n==2&&k==1) {puts("impossible"); return 0;}
	if(k==0) {for(int i=0;i<n;i++) printf("S"); return 0;}
	if(k==n) {for(int i=0;i<n;i++) printf("N"); return 0;}
	bool swapped=false;
	if(k>n-k) {k=n-k; swapped=true;}
	string s(n,'S');
	if(dir)
	{
		for(int i=2;i<=k+1;i++) s[i-1]='N';
	}
	else
	{
		dijkstra(1); for(int i=1;i<=n;i++) ds[i]=d[i];
		dijkstra(n); for(int i=1;i<=n;i++) dt[i]=d[i];
		memset(good,false,sizeof(good));
		for(int i=1;i<=n;i++) if(ds[i]+dt[i]-t[i]==ds[n]) good[i]=true;
		fill(nd+1,nd+n+1,INF);
		queue<int> que;
		nd[1]=0; que.push(1);
		s[0]='N'; k--;
		while(que.size())
		{
			int v=que.front(); que.pop();
			for(auto to:G[v])
			{
				if(good[to]&&ds[v]+t[to]==ds[to]&&nd[to]==INF)
				{
					if(k) {s[to-1]='N'; k--;}
					nd[to]=nd[v]+1;
					que.push(to);
				}
			}
		}
		if(k)
		{
			for(int i=1;i<=n;i++)
			{
				if(good[i]) continue;
				s[i-1]='N'; k--;
				if(!k) break;
			}
		}
	}
	if(swapped) {for(int i=1;i<=n;i++) s[i-1]='N'+'S'-s[i-1];}
	cout<<s<<endl;
	return 0;
}