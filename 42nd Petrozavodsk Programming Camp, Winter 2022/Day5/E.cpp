#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
int ans[1025][1025];
ll sum[1025][1025];
bool check()
{
	int cnt=(1<<(n-1));
	ll res=sum[cnt][cnt];
	for(int i=1;i<=cnt+1;i++)
		for(int j=1;j<=cnt+1;j++)
			if(sum[i+cnt-1][j+cnt-1]-sum[i+cnt-1][j-1]-sum[i-1][j+cnt-1]+sum[i-1][j-1]!=res) return false;
	return true;
}
int main()
{
	scanf("%d",&n);
	if(n==1)
	{
		puts("NO");
		return 0;
	}
	int l=1,r=(1<<(2*n));
	for(int i=1;i<=(1<<n);i++)
	{
		if(i&1)
		{
			for(int j=1;j<=(1<<n);j+=2) ans[i][j]=l,l++;
			for(int j=(1<<n);j>=1;j-=2) ans[i][j]=r,r--;
		}
		else
		{
			for(int j=2;j<=(1<<n);j+=2) ans[i][j]=r,r--;
			for(int j=(1<<n)-1;j>=1;j-=2) ans[i][j]=l,l++;
		}
	}
	/*for(int i=1;i<=(1<<n);i++)
		for(int j=1;j<=(1<<n);j++)
			sum[i][j]=ans[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	assert(check());*/
	puts("YES");
	for(int i=1;i<=(1<<n);i++)
	{
		for(int j=1;j<=(1<<n);j++) printf("%d ",ans[i][j]);
		puts("");
	}
	return 0;
}