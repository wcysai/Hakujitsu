#include<bits/stdc++.h>
#define MAXN 100020
#define MAXK 15
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define double long double
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const double eps=1e-9;
int n,k;
int l[MAXK],r[MAXK];
int ans[MAXN];
int bit[MAXN];
int sum(int i)
{
	int s=0;
	while(i>0)
	{
		s+=bit[i];
		i-=i&-i;
	}
	return s;
}
void add(int i,int x)
{
	while(i<=100005)
	{
		bit[i]+=x;
		i+=i&-i;
	}
}
const double PI=acos(-1);
struct node
{
	int x,y,id;
};
node a[MAXN],b[MAXN];
bool cmp(node p,node q)
{
	if(p.y!=q.y) return p.y>q.y;
	return p.x<q.x;
}
vector<double> dis;
void calc_right(int id)
{
	memset(bit,0,sizeof(bit));
	if(r[id]==90)
	{
		for(int i=0;i<n;i++)
		{
			ans[a[i].id]-=sum(50000-a[i].x);
			add(50001-a[i].x,1);
		}
		return;
	}
	double slope=-tan(r[id]/180.0*PI);
	if(slope>0)
	{
		dis.clear();
		for(int i=0;i<n;i++) dis.push_back(a[i].y-slope*a[i].x);
		sort(dis.begin(),dis.end());
		dis.push_back(INF);
		int sz=(int)dis.size();
		for(int i=0;i<n;i++)
		{
			int pos=lower_bound(dis.begin(),dis.end(),a[i].y-slope*a[i].x-eps)-dis.begin()+1;
			ans[a[i].id]-=sum(pos);
			add(pos+1,1);
		}
	}
	else
	{
		dis.clear();
		for(int i=0;i<n;i++) dis.push_back(a[i].y-slope*a[i].x);
		sort(dis.begin(),dis.end());
		dis.push_back(INF);
		int sz=(int)dis.size();
		for(int i=0;i<n;i++)
		{
			int pos=lower_bound(dis.begin(),dis.end(),a[i].y-slope*a[i].x+eps)-dis.begin()-1;
			ans[a[i].id]-=sum(sz-pos-1);
			add(sz-pos,1);
		}
	}
}
void calc_left(int id)
{
	memset(bit,0,sizeof(bit));
	if(l[id]==90)
	{
		for(int i=0;i<n;i++)
		{
			ans[a[i].id]-=sum(a[i].x);
			add(a[i].x+1,1);
		}
		return;
	}
	double slope=-tan(l[id]/180.0*PI);
	if(slope>0)
	{
		dis.clear();
		for(int i=0;i<n;i++) dis.push_back(a[i].y-slope*a[i].x);
		sort(dis.begin(),dis.end());
		dis.push_back(INF);
		int sz=(int)dis.size();
		for(int i=0;i<n;i++)
		{
			int pos=lower_bound(dis.begin(),dis.end(),a[i].y-slope*a[i].x-eps)-dis.begin()+1;
			ans[a[i].id]-=sum(sz-pos-1);
			add(sz-pos,1);
		}
	}
	else
	{
		dis.clear();
		for(int i=0;i<n;i++) dis.push_back(a[i].y-slope*a[i].x);
		sort(dis.begin(),dis.end());
		dis.push_back(INF);
		int sz=(int)dis.size();
		for(int i=0;i<n;i++)
		{
			int pos=lower_bound(dis.begin(),dis.end(),a[i].y-slope*a[i].x+eps)-dis.begin()-1;
			ans[a[i].id]-=sum(pos);
			add(pos+1,1);
		}
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].id=i;
	}
	sort(a,a+n,cmp);
	for(int i=0;i<k;i++) scanf("%d%d",&l[i],&r[i]);
	for(int i=0;i<n;i++) ans[a[i].id]=k*i;
	for(int i=0;i<k;i++)
	{
		calc_right(i);
		//for(int i=0;i<n;i++) printf("%d%c",ans[i],i==n-1?'\n':' ');
		calc_left(i);
	}
	for(int i=0;i<n;i++) printf("%d%c",ans[i],i==n-1?'\n':' ');
	return 0;
}