#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,a[MAXN];
int pow_mod(int a,int i,int m)
{
    int s=1%m;
    while(i)
    {
        if(i&1) s=1LL*s*a%m;
        a=1LL*a*a%m;
        i>>=1;
    }
    return s;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        int maxi=0;
        int g=0;
        bool f=true;
        for(int i=1;i<=n;i++) 
        {
            scanf("%d",&a[i]);
            maxi=max(maxi,a[i]);
            if(i<=30&&a[i]>(1<<(i-1))) f=false;
            else
            {
                if(g==0) g=((1<<(i-1))-a[i]);
                else
                {
                    int mod=((pow_mod(2,i-1,g)-a[i])%g+g)%g;
                    g=__gcd(g,mod);
                }
            }
        }
        if(g==0||maxi+1>g) f=false;
        if(maxi==0&&g==1) {puts("1"); continue;}
        if(!f) {puts("-1"); continue;}
        for(int i=maxi+1;1LL*i*i<=g;i++) if(g%i==0) {f=false; break;}
        if(!f) {puts("-1"); continue;} else printf("%d\n",g);
    }
    return 0;
}