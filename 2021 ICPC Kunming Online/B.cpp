#include<bits/stdc++.h>
#define MAXN 25
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,w,h;
int x[2][MAXN],y[2][MAXN];
vector<int> disx,disy;
int sum[25][25];
bool save[(1<<10)];
int dp[(1<<10)];
int pow_mod(int a,int i)
{
	int s=1;
	while(i)
	{
		if(i&1) s=1LL*s*a%MOD;
		a=1LL*a*a%MOD;
		i>>=1;
	}
	return s;
}
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void clear()
{
	memset(sum,0,sizeof(sum));
}
void print()
{
	int szx=(int)disx.size(); int szy=(int)disy.size();
	for(int i=0;i<szx;i++)
	{
		for(int j=0;j<szy;j++) printf("%d ",sum[i][j]);
		puts("");
	}
}
void add_rect(int id)
{
	//printf("add %d\n",id);
	sum[x[0][id]][y[0][id]]++;
	sum[x[0][id]][y[1][id]]--;
	sum[x[1][id]][y[0][id]]--;
	sum[x[1][id]][y[1][id]]++;
	//print();
}
void prefix_sum()
{
	int szx=(int)disx.size(); int szy=(int)disy.size();
	for(int i=0;i<szx;i++)
		for(int j=0;j<szy;j++)
			if(j!=0) sum[i][j]+=sum[i][j-1];
	for(int i=0;i<szx;i++)
		for(int j=0;j<szy;j++)
			if(i!=0) sum[i][j]+=sum[i-1][j];
	//print();
}
bool check_valid()
{
	int szx=(int)disx.size(); int szy=(int)disy.size();
	for(int i=0;i<szx-1;i++)
		for(int j=0;j<szy-1;j++)
			if(!sum[i][j]) return false;
	return true;
}
bool check_mask(int mask)
{
	clear();
	for(int i=0;i<n;i++)
		if(mask&(1<<i)) add_rect(i+1);
	prefix_sum();
	return check_valid(); 
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		disx.clear(); disy.clear();
		scanf("%d",&n);
		scanf("%d%d",&w,&h);
		x[0][0]=y[0][0]=0; x[1][0]=w; y[1][0]=h;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d%d%d",&x[0][i],&y[0][i],&x[1][i],&y[1][i]);
			x[1][i]=min(x[1][i],w); y[1][i]=min(y[1][i],h);
		}
		for(int i=0;i<=n;i++)
			for(int j=0;j<2;j++)
			{
				disx.push_back(x[j][i]); disy.push_back(y[j][i]);
			}
		sort(disx.begin(),disx.end()); disx.erase(unique(disx.begin(),disx.end()),disx.end());
		sort(disy.begin(),disy.end()); disy.erase(unique(disy.begin(),disy.end()),disy.end());
		for(int i=0;i<=n;i++)
		{
			for(int j=0;j<2;j++)
			{
				x[j][i]=lower_bound(disx.begin(),disx.end(),x[j][i])-disx.begin();
				y[j][i]=lower_bound(disy.begin(),disy.end(),y[j][i])-disy.begin();
			}
		} 
		//for(int i=0;i<=n;i++) printf("%d %d %d %d\n",x[0][i],y[0][i],x[1][i],y[1][i]);
		if(!check_mask((1<<n)-1)) {puts("-1"); continue;}
		save[(1<<n)-1]=true; save[0]=false;
		memset(save,false,sizeof(save));
		for(int i=1;i<(1<<n)-1;i++) save[i]=check_mask(i);
		memset(dp,0,sizeof(dp));
		int inv=pow_mod(n,MOD-2);
		for(int i=(1<<n)-1;i>=0;i--)
		{
			if(save[i]) dp[i]=0;
			else
			{
				int num=__builtin_popcount(i);
				int tmp=0;
				for(int j=0;j<n;j++) if(!(i&(1<<j))) add(tmp,dp[i^(1<<j)]%MOD);
				add(tmp,n);
				dp[i]=1LL*tmp*pow_mod(n-num,MOD-2)%MOD;
			}
		}
		printf("%d\n",dp[0]);
	}
	return 0;
}