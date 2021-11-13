#include<bits/stdc++.h>
#define MAXN 19
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef unsigned long long ull;
typedef pair<int,int> P;
int T,n;
string str;
int mask[18];
bool valid[(1<<18)];
int dp[(1<<18)];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++) 
        {
            cin>>str;
            int m=0;
            for(int j=0;j<n;j++) if(str[j]=='1') m+=1<<j;
            mask[i]=m;
        }
        for(int i=0;i<(1<<n);i++)
        {
            valid[i]=true;
            for(int j=0;j<n;j++) if((i&(1<<j))&&(mask[j]&i)) valid[i]=false;
        }
        dp[0]=0;
        for(int i=1;i<(1<<n);i++)
        {
            dp[i]=INF;
            int sub=i;
            do
            {
                if(valid[sub]) dp[i]=min(dp[i],dp[i^sub]+1);
                sub=(sub-1)&i;
            }while(sub!=0);
        }
        unsigned int ans=0,base=1;
        for(int i=1;i<(1<<n);i++)
        {
            base=base*233;
            ans=ans+base*dp[i];
        }
        printf("%u\n",ans);
    }
    return 0;
}