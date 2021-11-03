#include<bits/stdc++.h>
#define MAXN 55
#define MAXM 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,a[MAXN][MAXN],b[MAXN][MAXN];
int dp[MAXN][MAXM*MAXN];
int cost[MAXN][MAXM],maxi[MAXN];
vector<int> val[MAXN];
void upd(int &a,int b) {a=max(a,b);}
int solve()
{
    for(int i=1;i<=n;i++) val[i].clear(),maxi[i]=0;
    int ans=0,sum=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=-500;j<=500;j++)
        {
            cost[i][j+500]=0;
            int nxt=i+1; if(nxt>n) nxt=1;
            for(int k=1;k<=m;k++) if(a[i][k]+j==a[nxt][k]) cost[i][j+500]++;
            if(cost[i][j+500]) val[i].push_back(j);
            maxi[i]=max(maxi[i],cost[i][j+500]);
        }
        sum+=maxi[i];
    }
    for(int i=1;i<=n;i++) ans=max(ans,sum-maxi[i]);
    memset(dp,-1,sizeof(dp));
    dp[0][n*500]=0;
    for(int i=0;i<=n;i++)
        for(int j=-500*i;j<=500*i;j++)
        {
            if(dp[i][j+500*n]==-1) continue;
            for(auto x:val[i+1])
                upd(dp[i+1][j+500*n+x],dp[i][j+500*n]+cost[i+1][x+500]); 
        }
    ans=max(ans,dp[n][500*n]);
    return ans;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) 
        {
            scanf("%d",&a[i][j]);
            b[j][i]=a[i][j];
        }
    int ans=solve();
    swap(n,m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            a[i][j]=b[i][j];
    ans+=solve();
    printf("%d\n",ans);
    return 0;
}