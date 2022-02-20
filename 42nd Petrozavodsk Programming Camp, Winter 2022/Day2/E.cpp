#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 5005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,s[MAXN],e[MAXN],w[MAXN];
vector<int> dis;
ll dp[MAXN];
vector<P> r[MAXN];
vector<int> has[MAXN];
int main()
{
	scanf("%d%d",&n,&k);
	ll ss=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&s[i],&e[i],&w[i]); ss+=w[i];
		dis.push_back(s[i]); dis.push_back(e[i]);
	}
	sort(dis.begin(),dis.end());
	dis.erase(unique(dis.begin(),dis.end()),dis.end());
	for(int i=1;i<=n;i++)
	{
		s[i]=lower_bound(dis.begin(),dis.end(),s[i])-dis.begin()+1;
		e[i]=lower_bound(dis.begin(),dis.end(),e[i])-dis.begin()+1;
		r[e[i]].push_back(P(s[i],w[i]));
	}
	for(int i=1;i<=(int)dis.size();i++)
	{
		priority_queue<int,vector<int>,greater<int> > pque;
		for(auto p:r[i])
			has[p.F].push_back(p.S);
		ll sum=0;
		for(int j=i;j>=1;j--)
		{
			for(auto x:has[j]) 
			{
				pque.push(x); sum+=x; 
				if(pque.size()>k) sum-=pque.top(),pque.pop();
			} 
			dp[i]=max(dp[i],dp[j-1]+sum);
		}
	}
	printf("%lld\n",ss-dp[(int)dis.size()]);
	return 0;
}