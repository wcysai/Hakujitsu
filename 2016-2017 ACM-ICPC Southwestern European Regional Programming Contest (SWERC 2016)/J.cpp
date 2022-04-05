#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
int n,m;
db ans[10],prob[10];
int cnt[10];
db fact[10];
db eps=1e-6;
void dfs(int now,int rem)
{
	if(now==m+1)
	{
		if(rem) return;
		db p=fact[n-1];
		for(int i=1;i<=m;i++) if(cnt[i]) p=p/fact[cnt[i]]*pow(ans[i],cnt[i]);
		for(int i=1;i<=m;i++)
		{
			if(cnt[i]==0) prob[i]+=p;
			else if(cnt[i]==1) break;
		}
		return;
	}
	for(int i=0;i<=rem;i++) 
	{
		cnt[now]=i;
		dfs(now+1,rem-i);
	}
}
bool calc(db magic)
{
	memset(cnt,0,sizeof(cnt));
	memset(prob,0,sizeof(prob));
	dfs(1,n-1);
	pair<db,int> maxi=make_pair(-INF,0);
	pair<db,int> mini=make_pair(INF,0);
	for(int i=1;i<=m;i++)
	{
		if(prob[i]<eps) continue;
		maxi=max(maxi,make_pair(prob[i],i));
		mini=min(mini,make_pair(prob[i],i));
	}
	if(maxi.F<mini.F+eps) return true;
	for(int i=1;i<m;i++)
	{
		ans[i]+=(prob[i]-prob[i+1])/magic;
		ans[i+1]-=(prob[i]-prob[i+1])/magic;
	}
} 
int main()
{
	fact[0]=1.0;
	for(int i=1;i<=8;i++) fact[i]=1.0*i*fact[i-1];
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) ans[i]=1.0/m;
	db magic=10;
	int counter=0;
	while(!calc(magic)&&counter<10000) magic*=1.001,counter++;
	for(int i=1;i<=m;i++) printf("%.10Lf\n",ans[i]);
	puts("");
	return 0;
}