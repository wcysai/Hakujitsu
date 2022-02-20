#include<bits/stdc++.h>
#define MAXN 26
#define MAXM 2500000
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
vector<pair<P,int> > points;
int s[3],tot;
vector<int> dis;
int mask[3][MAXM];
int type[MAXM];
int m[3];
bool cmp(pair<P,int> &x,pair<P,int> &y)
{
	if(x.F.F!=y.F.F) return x.F.F<y.F.F;
	return x.F.S<y.F.S;
}
void dfs(int now,int r,int id)
{
	if(now>r)
	{
		tot++;
		type[tot]=id;
		for(int i=0;i<3;i++) mask[i][tot]=m[i];
		if(id==0) points.push_back(make_pair(P(s[0]-s[1],s[1]-s[2]),tot));
		else points.push_back(make_pair(P(s[1]-s[0],s[2]-s[1]),tot));
		return;
	}
	for(int i=0;i<3;i++)
	{
		s[i]+=a[now]; m[i]^=(1<<(now-1)); 
		dfs(now+1,r,id); 
		s[i]-=a[now]; m[i]^=(1<<(now-1));
	} 
}
int sz;
P bit[MAXM];
int res[MAXN];
P sum(int i)
{
    P s=P(-INF,0);
    while(i>0)
    {
        s=max(s,bit[i]);
        i-=i&-i;
    }
    return s;
}
void add(int i,P x)
{
    while(i<=sz)
    {
        bit[i]=max(bit[i],x);
        i+=i&-i;
    }
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	int x=n/2,y=n-x;
	dfs(1,x,0); dfs(x+1,n,1);
	for(auto p:points) dis.push_back(p.F.S);
	sort(dis.begin(),dis.end());
	dis.erase(unique(dis.begin(),dis.end()),dis.end());
	sort(points.begin(),points.end(),cmp);
	sz=(int)dis.size();
	for(int i=0;i<=sz;i++) bit[i]=P(-INF,0);
	int ans=INF;
	int best[3];
	for(auto p:points)
	{
		int id=lower_bound(dis.begin(),dis.end(),p.F.S)-dis.begin()+1;
		if(type[p.S]==0) 
		{
			P val=sum(id);
			if(val.F!=-INF&&ans>p.F.F+p.F.S-val.F) 
			{
				ans=p.F.F+p.F.S-val.F;
				for(int i=0;i<3;i++) best[i]=(mask[i][p.S]^mask[i][val.S]);
			}
		}
		else
		{
			add(id,P(p.F.F+p.F.S,p.S));
		}
	}
	assert(ans!=INF);
	for(int i=0;i<3;i++) 
		for(int j=0;j<n;j++)
			if(best[i]&(1<<j)) res[j+1]=i+1;
	for(int i=1;i<=n;i++)
	{
		assert(res[i]);
		printf("%d ",res[i]);
	}
	return 0;
}