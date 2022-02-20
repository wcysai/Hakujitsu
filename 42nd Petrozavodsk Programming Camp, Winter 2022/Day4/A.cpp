#include<bits/stdc++.h>
#define MAXN 25
#define MAXD 360
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
bool circ[MAXN][MAXD];
bool vert[MAXN][MAXD];
deque<pair<P,int> > deq;
int dist[MAXN][MAXD][MAXD];
//state: circle, degree, rotation
bool drop_prev(int deg)
{
	if(deg>=315) return true;
	if(deg<=45) return true;
	return false;
}
bool drop_next(int deg)
{
	if(deg>=135&&deg<=225) return true;
	return false;
}
bool dir_drop_prev(int deg)
{
	if(deg>=271) return true;
	if(deg<=89) return true;
	return false;
}
bool dir_drop_next(int deg)
{
	if(deg>=91&&deg<=269) return true;
	return false;
}
int get_dir(int deg)
{
	if(deg==0||deg==180) return 0;
	else if(deg<180) return 1;
	else return -1;
}
int get_next(int deg)
{
	deg++;
	if(deg==360) deg=0;
	return deg;
}
int get_prev(int deg)
{
	deg--;
	if(deg==-1) deg=359;
	return deg;
}
pair<P,int> go(int circle,int degree,int rotation)
{
	int curdeg=degree+rotation;
	if(curdeg>=360) curdeg-=360;
	if(circ[circle][degree])
	{
		if(circle!=n&&vert[circle][degree]&&drop_next(curdeg)) return make_pair(P(circle+1,degree),rotation);
		if(circle!=1&&vert[circle-1][degree]&&drop_prev(curdeg)) return make_pair(P(circle-1,degree),rotation);
		int dir=get_dir(curdeg);
		if(dir==0) 
		{
			//if(circle!=n&&vert[circle][degree]&&dir_drop_next(curdeg)) return make_pair(P(circle+1,degree),rotation);
			//if(circle!=1&&vert[circle-1][degree]&&dir_drop_prev(curdeg)) return make_pair(P(circle-1,degree),rotation);
			return make_pair(P(circle,degree),rotation);
		}
		else if(dir==1)
		{
			int ndeg=get_next(degree);
			if(circ[circle][ndeg]) return make_pair(P(circle,ndeg),rotation);
			if(circle!=n&&vert[circle][degree]&&dir_drop_next(curdeg)) return make_pair(P(circle+1,degree),rotation);
			if(circle!=1&&vert[circle-1][degree]&&dir_drop_prev(curdeg)) return make_pair(P(circle-1,degree),rotation);
			return make_pair(P(circle,degree),rotation);
		}
		else
		{
			int ndeg=get_prev(degree);
			if(circ[circle][ndeg]) return make_pair(P(circle,ndeg),rotation);
			if(circle!=n&&vert[circle][degree]&&dir_drop_next(curdeg)) return make_pair(P(circle+1,degree),rotation);
			if(circle!=1&&vert[circle-1][degree]&&dir_drop_prev(curdeg)) return make_pair(P(circle-1,degree),rotation);
			return make_pair(P(circle,degree),rotation);
		}
	}
	if(circle!=n&&vert[circle][degree]&&dir_drop_next(curdeg)) return make_pair(P(circle+1,degree),rotation);
	if(circle!=1&&vert[circle-1][degree]&&dir_drop_prev(curdeg)) return make_pair(P(circle-1,degree),rotation);
	return make_pair(P(circle,degree),rotation);
}
int main()
{
	scanf("%d",&n);
	memset(circ,false,sizeof(circ));
	memset(vert,false,sizeof(vert));
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		for(int j=0;j<x;j++)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			int now=l;
			do
			{
				circ[i][now]=true;
				if(now==r) break;
				now=get_next(now);
			}while(true);
		}
		scanf("%d",&x);
		for(int j=0;j<x;j++)
		{
			int pos;
			scanf("%d",&pos);
			vert[i][pos]=true;
		}
	}
	int sx,sy,tx,ty;
	scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
	sx++; tx++;
	for(int i=1;i<=n;i++)
		for(int j=0;j<360;j++)
			for(int k=0;k<360;k++)
				dist[i][j][k]=INF;
	dist[sx][sy][0]=0; deq.push_back(make_pair(P(sx,sy),0));
	while(deq.size())
	{
		auto p=deq.front(); deq.pop_front();
		int d=dist[p.F.F][p.F.S][p.S];
		auto q=go(p.F.F,p.F.S,p.S);
		if(q==p)
		{
			p.S=get_prev(p.S);
			if(dist[p.F.F][p.F.S][p.S]==INF)
			{
				dist[p.F.F][p.F.S][p.S]=d+1;
				deq.push_back(p);
			}
			p.S=get_next(p.S);
			p.S=get_next(p.S);
			if(dist[p.F.F][p.F.S][p.S]==INF)
			{
				dist[p.F.F][p.F.S][p.S]=d+1;
				deq.push_back(p);
			}
			p.S=get_prev(p.S);
		}
		else if(dist[q.F.F][q.F.S][q.S]==INF)
		{
			dist[q.F.F][q.F.S][q.S]=d;
			deq.push_front(q);
		}
	}
	int ans=INF;
	for(int deg=0;deg<360;deg++) 
		if(go(tx,ty,deg)==make_pair(P(tx,ty),deg)) ans=min(ans,dist[tx][ty][deg]);
	if(ans==INF) puts("Impossible"); else printf("%d\n",ans);
	return 0;
}