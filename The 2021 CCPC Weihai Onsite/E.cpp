#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long double db;
typedef long long ll;
typedef pair<int,int> P;
int n,q,k;
int a[MAXN],cnt[MAXN],sum[MAXN];
db sumval[MAXN];
vector<int> val;
db dp[MAXN];
const db eps=1e-10;
int cmp(db x,db y)
{
    if(abs(x-y)<eps) return 0;
    if(x<y) return -1; else return 1;
}
int main()
{
    scanf("%d%d%d",&n,&k,&q);
    db s=0;
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&a[i]);
        if(!cnt[a[i]]) val.push_back(a[i]);
        cnt[a[i]]++; sumval[a[i]]+=a[i];
        s+=a[i];
    }
    sum[0]=cnt[0];
    for(int i=1;i<=1000000;i++) sum[i]=sum[i-1]+cnt[i],sumval[i]=sumval[i-1]+sumval[i];
    dp[0]=2.0*s/n;
    for(int i=1;i<=k;i++)
    {
        dp[i]=0.0;
        for(auto x:val)
        {
            db p=1.0*cnt[x]/n,q;
            int need=max(0,(int)(dp[i-1]-eps-x));
            while(need+x<dp[i-1]) need++;
            //printf("x=%d need=%d\n",x,need);
            if(need>1000000) {dp[i]+=p*dp[i-1]; continue;}
            db s=(need==0?sumval[1000000]-x:sumval[1000000]-sumval[need-1]-(x>=need?x:0));
            int num=(need==0?n-1:sum[1000000]-sum[need-1]-(x>=need?1:0));
            //printf("s=%.10f num=%d\n",s,num);
            if(num==0) {dp[i]+=p*dp[i-1]; continue;}
            q=1.0*num/(n-1);
            dp[i]+=p*(q*(x+s/num)+(1-q)*dp[i-1]);
        }
        //printf("%d %.10f\n",i,dp[i]);
    }
    printf("%.10Lf\n",dp[k]);
    for(int i=0;i<q;i++)
    {
        int x,y,c;
        scanf("%d%d%d",&x,&y,&c);
        if(c==0) {puts("accept"); continue;}
        db sum=a[x]+a[y];
        int sgn=cmp(sum,dp[c-1]);
        if(!sgn) puts("both"); else if(sgn<0) puts("reselect"); else puts("accept");
    }
    return 0;
}