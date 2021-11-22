#include<bits/stdc++.h>
#define MAXN (1<<25)
#define MAXM 100005
#define INF 100000000
#define MOD 100000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q;
string str[MAXM];
string s[5];
int cnt[MAXN],sb[MAXN],sp[MAXN];
bool check(int mask0,int mask1,int maskq)
{
    if(__builtin_popcount(mask1)<=__builtin_popcount(mask0))
    {
        int sum=0;
        int sub=mask1;
        do
        {
            if(__builtin_popcount(sub)&1) sum-=sb[maskq|(mask1^sub)]; else sum+=sb[maskq|(mask1^sub)];
            sub=(sub-1)&mask1;
        }while(sub!=mask1);
        if(sum) return true; else return false;
    }
    else
    {
        int sum=0;
        int sub=mask0;
        do
        {
            if(__builtin_popcount(sub)&1) sum-=sp[mask1|sub]; else sum+=sp[mask1|sub];
            sub=(sub-1)&mask0;
        }while(sub!=mask0);
        if(sum) return true; else return false;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        cin>>str[i];
        int mask=0;
        for(int j=0;j<(int)str[i].size();j++)
        {
            if(str[i][j]=='z') continue;
            mask|=(1<<(str[i][j]-'a'));
            if(!cnt[mask]) {sb[mask]++; sp[mask]++; cnt[mask]=i+1;} 
        }
    }
    scanf("%d",&q);
    for(int i=0;i<25;i++)
        for(int j=0;j<(1<<25);j++)
            if(j&(1<<i)) sb[j]+=sb[j^(1<<i)]; else sp[j]+=sp[j^(1<<i)];
    for(int i=0;i<q;i++)
    {
        for(int j=0;j<5;j++) cin>>s[j];
        int mask0=0,mask1=0,maskq=0;
        for(int j=0;j<5;j++)
            for(int k=0;k<5;k++)
                if(s[j][k]>='A'&&s[j][k]<='Z') maskq|=(1<<(5*j+k));
                else if(s[j][k]=='r') mask1|=(1<<(5*j+k));
                else mask0|=(1<<(5*j+k));
        bool f=false;
        if(__builtin_popcount(maskq)>8)
        {
            int res=__builtin_popcount(maskq);
            for(int i=0;i<res-8;i++)
            {
                int pos=__builtin_ffs(maskq)-1;
                maskq^=(1<<pos); mask0^=(1<<pos);
                if(!check(mask0,mask1,maskq)) mask0^=(1<<pos),mask1^=(1<<pos);
            }
        }
        int sub=maskq;
        do
        {
            if(cnt[sub^mask1]) {cout<<str[cnt[sub^mask1]-1]; printf(" %d\n",9); f=true; break;}
            sub=(sub-1)&maskq;
        }while(sub!=maskq);
        if(!f) {puts("IMPOSSIBLE"); continue;}
    }
    return 0;
}