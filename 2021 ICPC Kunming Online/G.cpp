#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
double p[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lf",&p[i]);
	double ans=0.0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(j==i) continue;
			ans+=p[i]*p[j]/(p[i]+p[j]);
		}
	}
	printf("%.15f\n",ans);
	return 0;
}