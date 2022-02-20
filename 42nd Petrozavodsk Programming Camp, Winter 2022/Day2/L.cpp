#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 105
#define MAXM 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
string str[MAXN];
bool isnum[MAXN][MAXN];
int dx[MAXN][MAXN],dy[MAXN][MAXN];
int lab[MAXN][MAXN],tot;
vector<int> G[MAXM];
int match[MAXM];
bool used[MAXM];
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
bool dfs(int v)
{
    used[v]=true;
    for(int i=0;i<G[v].size();i++)
    {
        int u=G[v][i],w=match[u];
        if(w<0||!used[w]&&dfs(w))
        {
            match[v]=u;
            match[u]=v;
            return true;
        }
    }
    return false;
}
int bipartite_matching()
{
    int res=0;
    memset(match,-1,sizeof(match));
    for(int v=1;v<=tot;v++)
    {
        if(match[v]<0)
        {
            memset(used,0,sizeof(used));
            if(dfs(v))
            {
                res++;
            }
        }
    }
    return res;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) cin>>str[i];
	bool f=true;
	int num=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			if(str[i][j]>='1'&&str[i][j]<='4')
			{
				isnum[i][j]=true;
				if(str[i][j]=='1'||str[i][j]=='2') dx[i][j]=0; else dx[i][j]=1;
				if(str[i][j]=='1'||str[i][j]=='3') dy[i][j]=0; else dy[i][j]=1;
			}
			else if(str[i][j]=='x') num++;
		}
	for(int i=0;i<n;i++)
	{
		vector<int> id; int last=-1,dir,curdir;
		for(int j=0;j<=m;j++)
		{
			if(j==m||isnum[i][j])
			{
				if(last==-1) dir=0; else dir=dx[i][last];
				if(j==m) curdir=1; else curdir=dx[i][j];
				if(((j-last)&1)^dir^curdir)
				{
					if(!id.size()) { puts("-1"); return 0;}
					bool flag=false;
					for(auto x:id) if(str[i][x]=='x') {flag=true; break;}
					if(!flag)
					{
						tot++;
						for(auto x:id) lab[i][x]=tot;
					}
				}
				id.clear();
				last=j;
			}
			else if(j<m&&str[i][j]!='o') id.push_back(j);
		}
	}
	for(int j=0;j<m;j++)
	{
		vector<int> id; int last=-1,dir,curdir;
		for(int i=0;i<=n;i++)
		{
			if(i==n||isnum[i][j])
			{
				if(last==-1) dir=0; else dir=dy[last][j];
				if(i==n) curdir=1; else curdir=dy[i][j];
				if(((i-last)&1)^dir^curdir)
				{
					if(!id.size()) { puts("-1"); return 0;}
					bool flag=false;
					for(auto x:id) if(str[x][j]=='x') {flag=true; break;}
					if(!flag)
					{
						tot++;
						for(auto x:id) if(lab[x][j]) add_edge(lab[x][j],tot);
					}
				}
				id.clear();
				last=i;
			}
			else if(i<n&&str[i][j]!='o') id.push_back(i);
		}
	}
	printf("%d\n",n*m-num-(tot-bipartite_matching()));
	return 0;
}