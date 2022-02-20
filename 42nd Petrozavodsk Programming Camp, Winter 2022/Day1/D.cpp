#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],b[MAXN];
int solve(int x,int y)
{
	if(y%2==1) return x&1;
	else 
	{
		int mod=x%(y+1);
		if(mod==y) return 2;
		else return mod&1;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	int sg=0;
	for(int i=1;i<=n;i++) sg^=solve(a[i],b[i]);
	if(sg) puts("Alice"); else puts("Bob");
	return 0;
}