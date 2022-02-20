#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 500005
#define MAXM 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
int dp[MAXN];
vector<int> young[MAXM];
void ins(int v)
{
    for(int i=1;;i++)
    {
        if(!young[i].size()||v>=young[i].back())
        {
            young[i].push_back(v);
            break;
        }
        int pos=upper_bound(young[i].begin(),young[i].end(),v)-young[i].begin();
        swap(young[i][pos],v);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    fill(dp,dp+n,INF);
    for(int i=1;i<=n;i++) *lower_bound(dp,dp+n,a[i])=a[i];
    int len=lower_bound(dp,dp+n,INF)-dp;
	if(1LL*len*len>=n)
	{
		for(int i=1;i<=n;i++) ins(a[i]);
		int cnt=1;
		for(int i=2;;i++) if(young[i].size()==young[1].size()) cnt++; else break;
		printf("%d\n",n-cnt);
	}
	else
	{
		for(int i=n;i>=1;i--) ins(a[i]);
		int cnt=0;
		for(int i=1;;i++) if(!young[i+1].size()) {cnt=young[i].size(); break;}
		printf("%d\n",n-cnt);
	}
    return 0;
}