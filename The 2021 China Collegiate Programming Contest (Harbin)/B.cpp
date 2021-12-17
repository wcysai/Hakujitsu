#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],dp[MAXN],last[MAXM];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int ans=0;
    for(int sum=2;sum<=200;sum++)
    {
        memset(dp,0,sizeof(dp));
        memset(last,-1,sizeof(last));
        for(int i=1;i<=n;i++)
        {
            dp[i]=dp[i-1];
            if(sum-a[i]>=1&&sum-a[i]<=100&&last[sum-a[i]]!=-1) dp[i]=max(dp[i],dp[last[sum-a[i]]-1]+1);
            last[a[i]]=i;
        }
        ans=max(ans,dp[n]);
    }
    printf("%d\n",2*ans);
    return 0;
}