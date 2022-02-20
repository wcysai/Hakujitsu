#include<bits/stdc++.h>
#define MAXN (1<<20)
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
int n;
P a[MAXN],b[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=0;i<(1<<n);i++)
	{
		int x;
		scanf("%lld",&x); 
		a[i].S=x; 
	}
	for(int i=0;i<n;i++)
	{
		for(int mask=0;mask<(1<<n);mask++)
		{
			if(mask&(1<<i))
			{
				b[mask].F=a[mask].S;
				b[mask].S=a[mask].F;
				b[mask].F+=a[mask^(1<<i)].F;
				b[mask].S+=a[mask^(1<<i)].S;
			}
			else
			{
				b[mask].F=a[mask].F;
				b[mask].S=a[mask].S;
				b[mask].F+=a[mask^(1<<i)].F;
				b[mask].S+=a[mask^(1<<i)].S;
			}
		}
		for(int mask=0;mask<(1<<n);mask++) a[mask]=b[mask];
	}
	for(int mask=0;mask<(1<<n);mask++) printf("%lld ",a[mask].F);
	return 0;
}