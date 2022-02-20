#include<bits/stdc++.h>
#define MAXN 21
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[(1<<20)];
int delta[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=0;i<(1<<n);i++) scanf("%d",&a[i]);
	for(int mask=0;mask<(1<<n);mask++)
	{
		for(int i=0;i<n;i++) 
		{
			if(mask&(1<<i)) continue;
			for(int j=0;j<n;j++)
			{
				if(i==j) continue;
				if(mask&(1<<j)) continue;
				if(a[mask^(1<<i)]-a[mask]<a[mask^(1<<i)^(1<<j)]-a[mask^(1<<j)])
				{
					printf("%d %d\n",mask^(1<<i),mask^(1<<j));
					return 0;
				}
			}
		}
	}
	puts("-1");
	return 0;
}