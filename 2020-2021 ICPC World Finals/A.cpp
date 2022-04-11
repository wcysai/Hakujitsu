#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int r,c;
int p,i,j,s;
int calc_dist(int x,int y)
{
	int xdis,ydis;
	if(x<=(r+1)/2) xdis=(r+1)/2-x; else xdis=x-(r+2)/2;
	if(y<=(c+1)/2) ydis=(c+1)/2-y; else ydis=y-(c+2)/2;
	return xdis+ydis;
}
void check(int y)
{
	int lb=1,rb=r;
	int cnt=0;
	while(lb<rb)
	{
		ll lid=1LL*(y-1)*r+lb,rid=1LL*(y-1)*r+rb;
		int nlb,nrb;
		nlb=max(1LL*lb,(lid-1)/c+1); nrb=min(1LL*rb,(rid-1)/c+1); cnt++;
		if(nlb==lb&&nrb==rb)
		{
			if(lb!=rb) return;
			else break;
		}
		lb=nlb; rb=nrb;
	}
	int x=lb,save=y;
	y=(1LL*(y-1)*r+lb)-1LL*(x-1)*c;
	if(i==0||calc_dist(x,y)<calc_dist(i,j))
	{
		p=save;
		i=x;
		j=y;
		s=cnt+1;
	}
}
int main()
{
	scanf("%d%d",&r,&c);
	i=0; j=0;
	for(int y=1;y<=c;y++) check(y);
	printf("%d %d %d %d\n",p,i,j,s);
	return 0;
}