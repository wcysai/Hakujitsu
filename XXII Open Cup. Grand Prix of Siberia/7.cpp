#include<bits/stdc++.h>
#define MAXN 200005
#define MAXM 405
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> P;
int t,n;
vector<P> v;
int ans[MAXN];
db dp[MAXM][2],ndp[MAXM][2];
int main()
{
    scanf("%d",&t);
    for(int i=0;i<t;i++)
    {
        scanf("%d",&n);
        v.push_back(P(n,i));  
    }
    sort(v.begin(),v.end());
    int now=0;
    for(int sum=0;sum<=200000;sum++)
    {
        //printf("sum=%d\n",sum);
        for(int i=0;i<=min(400,sum);i++)
        {
            int j=sum-i;
            for(int k=0;k<2;k++)
            {
                if(i==0) ndp[i][k]=1.0;
                else if(i>j) ndp[i][k]=0.0;
                else 
                {
                    if(k==1) ndp[i][k]=dp[i][0];
                    else ndp[i][k]=dp[i-1][1]*i/(i+j)+dp[i][1]*j/(i+j);
                }
            }
        }
        swap(dp,ndp);
        while(now<(int)v.size()&&v[now].F==sum)
        {
            db dif=1.0;
            int res=-1;
            for(int i=0;i<=min(sum,400);i++) if(abs(dp[i][0]-0.5)<dif) {dif=abs(dp[i][0]-0.5); res=i;}
            ans[v[now].S]=res;
            now++;
        }
    }
    for(int i=0;i<t;i++) printf("%d\n",ans[i]);
    return 0;
}