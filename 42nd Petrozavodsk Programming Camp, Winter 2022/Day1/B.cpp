#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
char mp[MAXN][MAXN];
void construct(int sz)
{
	if(sz==0||sz==1) return;
	int st=(n-sz);
	for(int i=1;i<sz;i++) mp[st][st+i]='B';
	for(int i=2;i<sz;i++) mp[st+i][st+1]='B';
	construct(sz-2);
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			mp[i][j]='W';
	construct(n);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++) printf("%c",mp[i][j]);
		printf("\n");
	}
	return 0;
}