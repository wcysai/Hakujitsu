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
int n,k;
vector<P> v;
int dp[MAXN];
int t[MAXN];
vector<int> young[MAXM];
void ins(int v)
{
    for(int i=1;i<=k;i++)
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
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
		v.push_back(P(x,y));
    }
    sort(v.begin(),v.end());
	for(int i=0;i<(int)v.size();i++) ins(v[i].S);
	int ans=0;
	for(int i=1;i<=k;i++) ans+=(int)young[i].size();
	printf("%d\n",ans);
    return 0;
}
