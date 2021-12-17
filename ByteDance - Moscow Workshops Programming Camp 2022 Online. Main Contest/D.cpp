#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
int fact[MAXN],invf[MAXN];
string str[MAXN];
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
    fact[0]=invf[0]=1;
    for(int i=1;i<=200000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[200000]=pow_mod(fact[200000],MOD-2);
    for(int i=199999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d",&n);
    int w=0,b=0,q=0;
    for(int i=1;i<=n;i++)
    {
        cin>>str[i];
        if(str[i][0]=='W') w++; else if(str[i][0]=='B') b++; else q++;
        if(str[i][1]=='W') w++; else if(str[i][1]=='B') b++; else q++;
    }
    if(w+q<b||b+q<w) {puts("0"); return 0;}
    int x=(b+q+w)/2-b,ans=comb(q,x);
    int res=1;
    for(int i=1;i<=n;i++) 
    {
        int cnt=0;
        if(str[i]=="WW"||str[i]=="BB") {res=0; break;}
        if((str[i][0]=='W'||str[i][0]=='?')&&(str[i][1]=='B'||str[i][1]=='?')) cnt++;
        if((str[i][0]=='B'||str[i][0]=='?')&&(str[i][1]=='W'||str[i][1]=='?')) cnt++;
        res=1LL*res*cnt%MOD;
    }
    dec(ans,res);
    res=1;
    for(int i=1;i<=n;i++) 
    {
        int cnt=0;
        if(str[i]=="WW"||str[i]=="BB") {res=0; break;}
        if((str[i][0]=='W'||str[i][0]=='?')&&(str[i][1]=='B'||str[i][1]=='?')) cnt++;
        res=1LL*res*cnt%MOD;
    }
    add(ans,res);
    res=1;
    for(int i=1;i<=n;i++) 
    {
        int cnt=0;
        if(str[i]=="WW"||str[i]=="BB") {res=0; break;}
        if((str[i][0]=='B'||str[i][0]=='?')&&(str[i][1]=='W'||str[i][1]=='?')) cnt++;
        res=1LL*res*cnt%MOD;
    }
    add(ans,res);
    printf("%d\n",ans);
    return 0;
}
