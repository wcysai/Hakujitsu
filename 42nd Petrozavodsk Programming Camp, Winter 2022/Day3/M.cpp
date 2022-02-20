#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=998244353;
ll pow_mod(ll a,ll i)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=s*a%mod;
        a=a*a%mod;
        i>>=1;
    }
    return s;
}
int dp[MAXN][3][4];
//in the form of a+b*c
//second dimension: ending with digit/+/*
//third dimension: 1/a+bc/ b/ bc 
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
namespace linear_seq
{
    const int N=10010;
    ll res[N],base[N],_c[N],_md[N];
    vector<ll> Md;
    void mul(ll *a,ll *b,int k)
    {
        rep(i,0,k+k) _c[i]=0;
        rep(i,0,k) if(a[i]) rep(j,0,k) _c[i+j]=(_c[i+j]+a[i]*b[j])%mod;
        for(int i=k+k-1;i>=k;i--)
            if(_c[i]) rep(j,0,SZ(Md)) _c[i-k+Md[j]]=(_c[i-k+Md[j]]-_c[i]*_md[Md[j]])%mod;
        rep(i,0,k) a[i]=_c[i];
    }
    int solve(ll n,VI a,VI b)//a:coefficient b:initial value b[n+1]=a[0]*b[n]+...
    {
        ll ans=0,pnt=0;
        int k=SZ(a);
        assert(SZ(a)==SZ(b));
        rep(i,0,k) _md[k-1-i]=-a[i];
        _md[k]=1;
        Md.clear();
        rep(i,0,k) if(_md[i]!=0) Md.push_back(i);
        rep(i,0,k) res[i]=base[i]=0;
        res[0]=1;
        while((1ll<<pnt)<=n) pnt++;
        for(int p=pnt;p>=0;p--)
        {
            mul(res,res,k);
            if((n>>p)&1)
            {
                for(int i=k-1;i>=0;i--) res[i+1]=res[i];
                res[0]=0;
                rep(j,0,SZ(Md)) res[Md[j]]=(res[Md[j]]-res[k]*_md[Md[j]])%mod;
            }
        }
        rep(i,0,k) ans=(ans+res[i]*b[i])%mod;
        if(ans<0) ans+=mod;
        return ans;
    }
    VI BM(VI s)
    {
        VI C(1,1),B(1,1);
        int L=0,m=1,b=1;
        rep(n,0,SZ(s))
        {
            ll d=0;
            rep(i,0,L+1) d=(d+(ll)C[i]*s[n-i])%mod;
            if(d==0) ++m;
            else if(2*L<=n)
            {
                VI T=C;
                ll c=mod-d*pow_mod(b,mod-2)%mod;
                while(SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                L=n+1-L;B=T;b=d;m=1;
            }
            else
            {
                ll c=mod-d*pow_mod(b,mod-2)%mod;
                while(SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                ++m;
            }
        }
        return C;
    }
    int gao(VI a,ll n)
    {
        VI c=BM(a);
        c.erase(c.begin());
        rep(i,0,SZ(c)) c[i]=(mod-c[i])%mod;
        return solve(n,c,VI(a.begin(),a.begin()+SZ(c)));
    }
}
ll n;
int main()
{
	memset(dp,0,sizeof(dp));
	dp[0][1][0]=dp[0][1][2]=1;
	for(int i=0;i<400;i++)
		for(int j=0;j<3;j++)
		{
			//use add
			if(j==0)
			{
				add(dp[i+1][1][0],dp[i][0][0]);
				add(dp[i+1][1][1],dp[i][0][1]);
				add(dp[i+1][1][2],dp[i][0][0]);
			}
			//use mult
			if(j==0)
			{
				add(dp[i+1][2][0],dp[i][0][0]);
				add(dp[i+1][2][1],dp[i][0][1]);
				dec(dp[i+1][2][1],dp[i][0][3]);
				add(dp[i+1][2][2],dp[i][0][3]);
			}
			for(int d=1;d<=9;d++)
			{
				add(dp[i+1][0][0],dp[i][j][0]);
				add(dp[i+1][0][1],dp[i][j][1]);
				add(dp[i+1][0][1],9LL*dp[i][j][3]%MOD);
				add(dp[i+1][0][1],1LL*d*dp[i][j][2]%MOD);
				add(dp[i+1][0][2],dp[i][j][2]);
				add(dp[i+1][0][3],10LL*dp[i][j][3]%MOD);
				add(dp[i+1][0][3],1LL*d*dp[i][j][2]%MOD);
			}
		}
	vector<int> v;
	for(int i=1;i<=400;i++) v.push_back(dp[i][0][1]);
	scanf("%lld",&n);
	printf("%d\n",linear_seq::gao(v,n-1));
	return 0;
}