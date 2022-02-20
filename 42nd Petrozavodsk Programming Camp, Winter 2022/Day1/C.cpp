#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
vector<P> st;//0: box 1: coin
vector<int> B,C;
vector<pair<P,int> > intervals;//0: coin-box 1: box-coin
ll dp[MAXN][2];//0: finish left 1: finish anywhere
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		B.push_back(x);
	}
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		C.push_back(x);
	}
	int l=0,r=0;
	while(l<n||r<n)
	{
		if(r>=n||(l<n&&B[l]<=C[r]))
		{
			if(st.size()&&st.back().S==1)
			{
				P p=st.back(); st.pop_back();
				if(!st.size()) intervals.push_back(make_pair(P(p.F,B[l]),0));
			}
			else st.push_back(P(B[l],0));
			l++;
		}
		else
		{
			if(st.size()&&st.back().S==0)
			{
				P p=st.back(); st.pop_back();
				if(!st.size()) intervals.push_back(make_pair(P(p.F,C[r]),1));
			}
			else st.push_back(P(C[r],1));
			r++;
		}
	}
	for(int i=(int)intervals.size()-1;i>=0;i--)
	{
		P p=intervals[i].F;
		int type=intervals[i].S;
		if(i==(int)intervals.size()-1)
		{
			int len=p.S-p.F;
			if(type==0)
			{
				dp[i][0]=2LL*len; dp[i][1]=len;
			}
			else
			{
				dp[i][0]=2LL*len; dp[i][1]=2LL*len;
			}
		}
		else
		{
			int len=p.S-p.F;
			if(type==0)
			{
				dp[i][0]=2LL*(len+intervals[i+1].F.F-p.S)+dp[i+1][0];
				dp[i][1]=(len+intervals[i+1].F.F-p.S)+dp[i+1][1];
			}
			else
			{
				dp[i][0]=2LL*(len+intervals[i+1].F.F-p.S)+dp[i+1][0];
				dp[i][1]=min(dp[i][0],3LL*len+intervals[i+1].F.F-p.S+dp[i+1][1]);
			}
		}
	}
	printf("%lld\n",intervals[0].F.F+dp[0][1]);
	return 0;
}