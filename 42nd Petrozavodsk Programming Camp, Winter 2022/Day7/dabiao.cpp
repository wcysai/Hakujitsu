#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define INV 499122177
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
double dp[100][100];
int main()
{
	dp[0][0]=1.0;
	for(int i=1;i<=20;i++)
	{
		for(int j=1;j<=i;j++)
		{
			dp[i][j]=0.5*(dp[i-1][j-1]+dp[i-1][j+1]);
			printf("i=%d j=%d dp=%.10f\n",i,j,dp[i][j]*pow(2.0,i));
		}
	}
}