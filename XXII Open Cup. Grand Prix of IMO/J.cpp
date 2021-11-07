#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],b[MAXN],c[MAXN];
bool used[MAXN];
int dp[MAXN][MAXN][MAXN];//current at i, maximum j,k specified
int fact[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int main()
{
    fact[0]=1;
    for(int i=1;i<=100;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=n;i++) c[a[i]]=b[i];
    memset(used,false,sizeof(used));
    int cnt=0;
    for(int i=1;i<=n;i++) {used[c[i]]=true; if(c[i]) cnt++;}
    dp[0][0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=n;j++)
        {
            for(int k=0;k<=n;k++)
            {
                //not add to increasing subsequence
                add(dp[i][j][k],dp[i-1][j][k]);
                //add to increasing subsequence
                if(c[i]==0&&(!used[j])&&k) 
                    for(int l=0;l<j;l++) add(dp[i][j][k],dp[i-1][l][k-1]);
                else if(c[i]>0&&c[i]==j)
                    for(int l=0;l<j;l++) add(dp[i][j][k],dp[i-1][l][k]);
            }
        }
    int ans=0;
    for(int i=0;i<=n;i++) 
        for(int j=0;j<=n-cnt;j++)
            add(ans,1LL*fact[n-cnt-j]*dp[n][i][j]%MOD);
    printf("%d\n",ans);
    return 0;
}