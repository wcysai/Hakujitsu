#include<bits/stdc++.h>
#define MAXN 26
#define MAXM 505
#define MAXS 505
#define INF 1000000000
#define MOD 1000000007
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
typedef vector<int> VI;
typedef long long ll;
typedef pair<ll,int> P;
typedef unsigned long long ULL;

const ll mod=1000000007;
ll m,n;
int q;
vector<P> ex;
map<int,int> cnt;
//to achieve best running time, sieve until 2/3 prime factors remaining
namespace pollardrho 
{
    ULL gcd(ULL a, ULL b) {return b ? gcd(b, a % b) : a;}

    ULL mulmod(ULL x,ULL y,ULL p)
    {
        ULL z=(long double)x/p*y;
        ULL res=(ULL)x*y-(ULL)z*p;
        return (res+p)%p;
    }

    ULL powmod(ULL b, ULL e, ULL m) 
    {
        ULL r = 1;
        while (e) 
        {
            if (e & 1) r = mulmod(r, b, m);
            b = mulmod(b, b, m);
            e >>= 1;
        }
        return r;
    }

    bool test(ULL n)
    {
        if (n < 3) return n==2;
        // ! The array a[] should be modified if the range of x changes.
        static const ULL a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23,  ULLONG_MAX};//works for 1e18
        ULL r = 0, d = n-1, x;
        while (~d & 1) d >>= 1, r++;
        for (int i=0; a[i] < n; i++)
        {
            x = powmod(a[i], d, n);
            if (x == 1 || x == n-1) goto next;
            for(int i=0;i<r;i++)
            {
                x = mulmod(x, x, n);
                if (x == n-1) goto next;
            }
            return false;
            next:;
        }
        return true;
    }

    map<ULL, int> mp;
    mt19937_64 gen(time(NULL));

    void PollardRho(ULL n) 
    {
        ULL c, x, y, d;
        while (n % 2 == 0) 
        {
            mp[2]++;
            n /= 2;
        }
        if (n == 1) return;

        if (test(n)) 
        {
            mp[n]++;
            return;
        }

        d = n;
        static int counter = 0;
        while (d == n) 
        {
            x = y = 2;
            d = 1;
            c = gen() % (n - 1) + 1;
            while (d == 1) 
            {
                counter++;
                x = (mulmod(x, x, n) + c) % n;
                y = (mulmod(y, y, n) + c) % n;
                y = (mulmod(y, y, n) + c) % n;
                d = gcd(x > y ? x - y : y - x, n);
            }
        }
        PollardRho(d);
        PollardRho(n / d);
    }

    void work(ULL n) 
    {
        PollardRho(n);
        for(auto p:mp) cnt[p.S]++;
        mp.clear();
    }
}
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
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int comb[40][40];
int pw[100][100];
int mult[40];
int encode(vector<int> &v)
{
	int code=0,num=1;
	for(int i=0;i<(int)ex.size();i++)
	{
		code+=v[i];
		num=num*(ex[i].S+1);
	}
	return code;
}
vector<int> decode(int code)
{
	printf("decode %d\n",code);
	vector<int> v;
	for(int i=0;i<(int)ex.size();i++)
	{
		v.push_back(code%(ex[i].S+1));
		code/=(ex[i].S+1);
	}
	for(auto x:v) printf("%d ",x);
	puts("");
	return v;
}
int get_ex(int code,int id)
{
	return (code%mult[id+1])/mult[id];
}
int calc(int state,int nstate)
{
	int all=1,cop=1;
	for(int i=0;i<(int)ex.size();i++)
	{
		int x=get_ex(state,i),y=get_ex(nstate,i);
		int ways;
		if(x+y<=(int)ex[i].S) ways=comb[ex[i].S-x][y]; else ways=0;
		int choices=pw[ex[i].F][y];
		all=1LL*all*comb[ex[i].S][y]%MOD*pw[ex[i].F][y]%MOD;
		cop=1LL*cop*ways*pw[ex[i].F][y]%MOD;
	}
	dec(all,cop);
	return all;
}
int dp[MAXM][MAXS];
int ans[MAXM];
int main()
{
	for(int i=0;i<100;i++)
	{
		pw[i][0]=1;
		for(int j=1;j<100;j++) pw[i][j]=1LL*pw[i][j-1]*i%MOD;
	}
	comb[0][0]=1;
	for(int i=1;i<=30;i++)
	{
		comb[i][0]=comb[i][i]=1;
		for(int j=1;j<i;j++) 
		{
			comb[i][j]=comb[i-1][j-1];
			add(comb[i][j],comb[i-1][j]);
		}
	}
	scanf("%lld%d",&m,&q);
	pollardrho::work(m);
	for(auto p:cnt) ex.push_back(p);
	int all,sz=(int)ex.size();
	mult[0]=1;
	for(int i=0;i<(int)ex.size();i++) mult[i+1]=mult[i]*(ex[i].S+1);
	all=mult[sz];
	dp[0][all-1]=1;
	VI coef;
	for(int i=0;i<400;i++)
	{
		ans[i]=0;
		for(int state=0;state<all;state++)
		{
			if(!dp[i][state]) continue;
			for(int nstate=0;nstate<all;nstate++)
				add(dp[i+1][nstate],1LL*dp[i][state]*calc(state,nstate)%MOD);
			add(ans[i],dp[i][state]);
		}
		coef.push_back(ans[i]);
	}
	VI c=linear_seq::BM(coef);
    c.erase(c.begin());
    rep(i,0,SZ(c)) c[i]=(mod-c[i])%mod;
	while(q--)
	{
		scanf("%lld",&n);
		int ans=linear_seq::solve(n,c,VI(coef.begin(),coef.begin()+SZ(c)));
		if(n==1) add(ans,1);
		printf("%d\n",ans);
	}
	return 0;
}