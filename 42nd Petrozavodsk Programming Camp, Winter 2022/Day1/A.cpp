#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,t;
vector<int> v;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		v.push_back(x);
	}
	scanf("%d",&t);
	sort(v.begin(),v.end());
	int now=0,ans=0,cur=0;
	while(now<(int)v.size())
	{
		int need=(v[now]-cur+t-1)/t;
		cur+=need*t;
		while(now<(int)v.size()&&v[now]<cur) now++;
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}