#include<bits/stdc++.h>
#define MAXN 100005
#define MAXV 400005
#define MAXM 5
#define INF 1000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
int n,a[MAXN];
ll x;
vector<int> items[MAXM];
ll dp[MAXV],ndp[MAXV];
int main()
{
	freopen("F.in","r",stdin);
	freopen("brute.out","w",stdout);
	scanf("%d%lld",&n,&x);
	int now=x%5; x-=x%5;
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&a[i]);
		if(a[i]%5) items[5-a[i]%5].push_back(a[i]-a[i]%5+5);
	}
	int s=0;
	for(int i=1;i<=4;i++) 
	{
		sort(items[i].begin(),items[i].end());
		s+=i*(int)items[i].size();
	}
	dp[0]=0;
	for(int i=1;i<=s;i++) dp[i]=INF;
	for(int w=1;w<=4;w++)
    {
		printf("i=%d\n",w);
        for(auto x:items[w]) printf("%d ",x);
        puts("");
        for(auto x:items[w])
        {
            for(int i=0;i<=s;i++) 
            {
                ndp[i]=dp[i];
                if(i>=w) ndp[i]=min(ndp[i],dp[i-w]+x);
            }
            swap(dp,ndp);
        }
		for(int i=0;i<=s;i++) printf("%lld ",dp[i]);
        puts("");
    }
    int ans=0;
    for(int i=s;i>=1;i--) if(dp[i]<=x) {ans=i; break;}
	printf("%d\n",ans+now);
	return 0;
}