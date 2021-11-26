#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 998244353
#define INV 499122177
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,fact[MAXN],invf[MAXN];
int prob[MAXN];
int invp3[MAXN],p2[MAXN];
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
int main()
{
    scanf("%d",&n);
    fact[0]=invf[0]=1;
    for(int i=1;i<=200000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[200000]=pow_mod(fact[200000],MOD-2);
    for(int i=199999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    int inv3=pow_mod(3,MOD-2);
    invp3[0]=p2[0]=1;
    for(int i=1;i<=200000;i++) invp3[i]=1LL*inv3*invp3[i-1]%MOD;
    for(int i=1;i<=200000;i++) p2[i]=2LL*p2[i-1]%MOD;
    //zero water, >=1 fire
    for(int i=1;2*i<n;i++) add(prob[i],1LL*(p2[i]-1)*invp3[i]%MOD);
    //one copy,  zero fire, >=1 water
    for(int i=2;i<n;i++) add(prob[i],1LL*i*invp3[i]%MOD);
    //zero copy, >=1 water
    int l=1,r=0,ans=0;
    for(int i=1;i<=n;i++)
    {
        //2s>3i-n-1
        //update
        ans=2LL*ans%MOD;
        add(ans,comb(i-1,l-1)); dec(ans,comb(i-1,r));
        int nl=max(1,(3*i+1-n)/2),nr=i;
        while(l>nl) {add(ans,comb(i,l-1)); l--;}
        while(l<nl) {dec(ans,comb(i,l)); l++;}
        while(r>nr) {dec(ans,comb(i,r)); r--;}
        while(r<nr) {add(ans,comb(i,r+1)); r++;}
        add(prob[i],1LL*ans*invp3[i]%MOD);
    }
    //one copy, >=1 fire, >=1 water
    l=1,r=0,ans=0;
    for(int i=3;i<=n;i++)
    {
        //2s>3i-n
        //update
        ans=2LL*ans%MOD;
        add(ans,comb(i-2,l-1)); dec(ans,comb(i-2,r));
        int nl=max(1,(3*i+2-n)/2),nr=i-2;
        if(nl>nr) continue;
        while(l>nl) {add(ans,comb(i-1,l-1)); l--;}
        while(l<nl) {dec(ans,comb(i-1,l)); l++;}
        while(r>nr) {dec(ans,comb(i-1,r)); r--;}
        while(r<nr) {add(ans,comb(i-1,r+1)); r++;}
        add(prob[i],1LL*ans*i%MOD*invp3[i]%MOD);
    }
    int sum=0;
    for(int i=1;i<=n;i++) add(sum,prob[i]);
    //all copy
    add(sum,3LL*INV%MOD);
    printf("%d\n",sum);
    return 0;
}
