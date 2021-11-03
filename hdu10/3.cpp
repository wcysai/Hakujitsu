#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<250000> bs;
int T,n;
bs dp[701];
bs test[701];
int main()
{
    for(int i=1;i<=700;i++) dp[i].reset();
    dp[0].set(0);
    dp[1].set(0);
    for(int i=2;i<=700;i++)
    {
        dp[i].reset();
        if(i<=140)
        {
            for(int j=1;j<=i;j++)
            {
                int shift=j*(i-j);
                dp[i]|=(dp[i-j]<<shift);
            }
        }
        else
        {
            for(int j=1;j<=min(i,70);j++)
            {
                int shift=j*(i-j);
                dp[i]|=(dp[i-j]<<shift);
            }
            for(int j=i;j>=max(i-70,i);j--)
            {
                int shift=j*(i-j);
                dp[i]|=(dp[i-j]<<shift);
            }
        }
    }
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=dp[n]._Find_first();i!=dp[n].size();i=dp[n]._Find_next(i)) printf("%d ",i);
        puts("");
    }
    return 0;
}