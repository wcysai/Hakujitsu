#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int b,l,d[MAXN];
int main()
{
    scanf("%d%d",&b,&l);
    for(int i=1;i<=l;i++) scanf("%d",&d[i]);
    int mod=0,p=b;
    for(int i=l;i>=1;i--)
    {
        mod=(mod+1LL*d[i]*p)%(b+1);
        p=b+1-p;
    }
    if(mod==0) {puts("0 0"); return 0;}
    for(int i=1;i<=l;i++)
    {
        if((l-i)&1)//+1
        {
            if(d[i]-mod>=0)
            {
                printf("%d %d\n",i,d[i]-mod);
                return 0;
            }
        }
        else 
        {
            if(d[i]-(b+1-mod)>=0)
            {
                printf("%d %d\n",i,d[i]-(b+1-mod));
                return 0;
            }
        }
    }
    puts("-1 -1");
    return 0;
}