#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int a[MAXN],ans[MAXN];
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
void init()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=100000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[100000]=pow_mod(fact[100000],MOD-2);
    for(int i=99999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
}
const int threshold=200;
int cnt[205];
vector<int> big;
int main()
{
    init();
    scanf("%d%d",&n,&m);
    int maxi=0,ans=1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        maxi=max(maxi,a[i]);
        if(a[i]<=threshold) cnt[a[i]]++; else big.push_back(a[i]);
        ans=1LL*ans*invf[a[i]]%MOD;
    }
    for(int i=1;i<maxi;i++) puts("0");
    for(int i=maxi;i<=m;i++)
    {
        int tmp=1,now=1;
        for(int k=i;k>=max(1,i-threshold+1);k--)
        {
            now=1LL*now*k%MOD;
            if(cnt[i-k+1]) tmp=1LL*tmp*pow_mod(now,cnt[i-k+1])%MOD;
        }
        for(auto x:big) tmp=1LL*tmp*fact[i]%MOD*invf[i-x]%MOD;
        printf("%d\n",1LL*ans*tmp%MOD);
    }
    return 0;
}