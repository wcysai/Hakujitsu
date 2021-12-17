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
        for(int i=1;i<=n;i++) 
            scanf("%d",&a[i]);
        bool flag=false;
        int m=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]!=(1<<(i-1)))
            {
                if(a[i]>(1<<(i-1)))
                {
                    break;
                }
                else
                {
                    flag=true;
                    m=(1<<(i-1))-a[i];
                    break;
                }
            }
        }
        if(!flag) {puts("-1"); continue;}
        flag=true;
        for(int i=1;i<=n;i++)
        {
            if(pow_mod(2,i-1,m)!=a[i])
            {
                flag=false;
                break;
            }
        }
        if(!flag) puts("-1"); else printf("%d\n",m);
    }
    return 0;
}