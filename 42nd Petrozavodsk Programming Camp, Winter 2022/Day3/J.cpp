#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
int dp[MAXN][MAXN*MAXN],ndp[MAXN][MAXN*MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int main()
{
	scanf("%d%d",&n,&k);
	dp[0][0]=1;
	for(int i=0;i<n;i++)
	{
		memset(ndp,0,sizeof(ndp));
		for(int save=0;save<=i;save++)
		{
			for(int j=0;j<=k;j++)
			{
				if(!dp[save][j]) continue;
				if(j+i+1<=k) add(ndp[save][j+i+1],(2LL*save+1)*dp[save][j]%MOD);
				if(save&&j+2*(i+1)<=k) add(ndp[save-1][j+2*(i+1)],1LL*save*save*dp[save][j]%MOD);
				add(ndp[save+1][j],dp[save][j]);
			}
		}
		swap(dp,ndp);
	}
	int fact=1;
	for(int i=1;i<=n;i++) fact=1LL*fact*i%MOD;
	fact=1LL*fact*dp[0][k]%MOD;
	printf("%d\n",fact);
	return 0;
}