#include<bits/stdc++.h>
#define MAXN 10
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,x,y;
int a[MAXN][MAXN],save[MAXN][MAXN],ans;
int d[MAXN][MAXN],deg[MAXN];
void floyd_warshall()
{
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
          for(int j=1;j<=n;j++) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}
bool check()
{
	for(int i=1;i<=n;i++) deg[i]=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(a[i][j]) {deg[i]++; deg[j]++;}
	int cnt=0;
	for(int i=1;i<=n;i++) 
	{
		if(!deg[i]) return false;
		if(deg[i]==1) cnt++;
	}
	if(cnt!=x) return false;
	memset(d,0,sizeof(d));
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(a[i][j]) d[i][j]=d[j][i]=1; else d[i][j]=d[j][i]=10;
	floyd_warshall();
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(d[i][j]>2) return false;
	return true;
}
void dfs(int i,int j,int now)
{
	if(i==n)
	{
		if(check()&&now<ans)
		{
			ans=now;
			for(int i=1;i<=n;i++)
			{
				for(int j=i+1;j<=n;j++)
					save[i][j]=a[i][j];
			}
		}
		return;
	}
	if(j==n+1) {dfs(i+1,i+2,now); return;}
	a[i][j]=1; dfs(i,j+1,now+1); a[i][j]=0;
	dfs(i,j+1,now);
}
int main()
{
	scanf("%d%d",&n,&x);
	ans=INF;
	dfs(1,2,0);
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
			printf("%d ",save[i][j]);
		puts("");
	}
	return 0;
}