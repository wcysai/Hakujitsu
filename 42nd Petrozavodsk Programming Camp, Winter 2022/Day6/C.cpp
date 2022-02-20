#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1005
#define MAXM 5005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,x[MAXN],cnt[MAXM];
int dp[MAXM];
int ind[MAXN],tot;
int main()
{
	scanf("%d%d",&n,&m);
	int magic=(int)sqrt(m);
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&x[i]);
		cnt[x[i]]++;
	}
	for(int i=1;i<=m;i++)
		if(cnt[i]) ind[++tot]=i;
	for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=0;j--)
		{
			if(i<=magic+1)
			{
				int val=dp[j]+cnt[0];
				for(int k=1;k<=tot;k++) if(ind[k]<=j) dp[j]=max(dp[j],dp[j-ind[k]]+cnt[ind[k]]); else break;
				dp[j]=max(dp[j],val);
			}
			else
			{
				int val=dp[j]+cnt[0];
				for(int k=1;k<=min(j,magic+1);k++) dp[j]=max(dp[j],dp[j-k]+cnt[k]);
				dp[j]=max(dp[j],val);
			}
		}
	}
	int ans=dp[m];
	printf("%.10f\n",1.0*ans/n);
	return 0;
}