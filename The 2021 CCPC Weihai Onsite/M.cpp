#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int fact[MAXN],invf[MAXN];
int n,m,k;
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

void init()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=100000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[100000]=pow_mod(fact[100000],MOD-2);
    for(int i=99999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
}
//n-m+1 variables, maximum = k sum =m
int solve(int n,int m,int k) //n variables, <=k, sum =m
{
    if(k<0) return 0;
    int ans=0;
    for(int i=0;i<=n;i++)
    {
        if(m<i*(k+1)) continue;
        int res=1LL*comb(n,i)*comb(m-i*(k+1)+(n-1),n-1)%MOD;
        if(i&1) dec(ans,res); else add(ans,res);
    }
    return ans;
}
int main()
{
    init();
    scanf("%d%d%d",&n,&m,&k);
    if(m>n||k>m) {puts("0"); return 0;}
    int ans=solve(n-m+1,m,k); dec(ans,solve(n-m+1,m,k-1));
    printf("%d\n",ans);
    return 0;
}