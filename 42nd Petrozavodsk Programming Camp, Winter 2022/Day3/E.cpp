#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k;
int fact[MAXN],invf[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
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
int comb(int n,int k)
{
	if(n<k) return 0;
	return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int A[MAXN][MAXN];
int det_mod(int n)
{
	int ans=1;
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			while(A[j][i]!=0)
			{
				int t=1LL*A[i][i]*pow_mod(A[j][i],MOD-2)%MOD;
				for(int k=0;k<n;k++)
				{
					dec(A[i][k],1LL*A[j][k]*t%MOD);
					swap(A[i][k],A[j][k]);
				}
				ans=(MOD-ans)%MOD;
			}
			if(A[i][i]==0) return 0;
		}
		ans=1LL*ans*A[i][i]%MOD;
	}
	return ans;
}
int main()
{
	fact[0]=invf[0]=1;
	for(int i=1;i<=500;i++) fact[i]=1LL*fact[i-1]*i%MOD;
	invf[500]=pow_mod(fact[500],MOD-2);
	for(int i=499;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<k;i++)
	{
		int x=-i,y=i;
		for(int j=0;j<k;j++)
		{
			int nx=m-j,ny=n+j;
			A[i][j]=comb(ny-y+nx-x,nx-x);
		}
	}
	printf("%d\n",det_mod(k));
	return 0;
}