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
ll dp[MAXV],ndp[MAXV],weight[MAXV];
void solve(int l,int r,int x,int y,int mod,int num)
{
    if(l>r) return;
    int mid=(l+r)/2;
    P p=P(INF,y);
    for(int i=x;i<=min(y,mid);i++)
        if(weight[(mid-i)*num]+dp[i*num+mod]<p.F) p=P(weight[(mid-i)*num]+dp[i*num+mod],i);
    ndp[mid*num+mod]=p.F;
    solve(l,mid-1,x,p.S,mod,num); solve(mid+1,r,p.S,y,mod,num);
}
int main()
{
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
	for(int i=1;i<=4;i++)
    {
        if(!items[i].size()) continue;
        for(int i=1;i<=s;i++) weight[i]=INF;
        weight[0]=0;
        for(int i=0;i<=s;i++) ndp[i]=INF;
        ll sum=0;
        for(int j=0;j<(int)items[i].size();j++)
        {
        	sum+=items[i][j];
            weight[i*(j+1)]=sum;
        }
        for(int j=0;j<i;j++)
            solve(0,(s-j)/i,0,(s-j)/i,j,i);
        swap(dp,ndp);
    }
    int ans=0;
    for(int i=s;i>=1;i--) if(dp[i]<=x) {ans=i; break;}
	printf("%d\n",ans+now);
	return 0;
}