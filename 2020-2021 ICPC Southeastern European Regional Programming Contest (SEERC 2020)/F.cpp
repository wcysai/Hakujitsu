#include<bits/stdc++.h>
#define MAXN 3005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,h[MAXN];
int L[MAXN],R[MAXN];
int st[MAXN];
int dp[MAXN][MAXN],sum[MAXN][MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&h[i]);
	int t=0;
	for(int i=1;i<=n;i++)
	{
		while(t>0&&h[st[t-1]]>=h[i]) t--;
		L[i]=t==0?0:st[t-1];
		st[t++]=i;
	}
	t=0;
	for(int i=n;i>=1;i--)
	{
		while(t>0&&h[st[t-1]]>=h[i]) t--;
		R[i]=t==0?n+1:st[t-1];
		st[t++]=i;
	}
    dp[0][0]=1;
    for(int i=0;i<=n;i++) sum[0][i]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            //not remain
            int l=L[i]+1,r=R[i]-1;
            add(dp[i][j],dp[i-1][j]);
            if(j>=l&&j<=r) 
            {
                add(dp[i][j],sum[i-1][j-1]);
                if(l>1) dec(dp[i][j],sum[i-1][l-2]);
            }
            sum[i][j]=dp[i][j];
            if(j>0) add(sum[i][j],sum[i][j-1]);
        }
    }
    printf("%d\n",dp[n][n]);
    return 0;
}
