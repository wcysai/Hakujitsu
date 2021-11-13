#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
mt19937 wcy(time(NULL));
int n,q;
int main()
{
    freopen("H.in","w",stdout);
    n=q=100000;
    printf("%d %d\n",n,q);
    for(int i=1;i<=n;i++) printf("%d ",wcy()%n+1);
    for(int i=0;i<q;i++)
    {
        int type,l,r,x;
        type=wcy()%3+1,l=wcy()%n+1,r=wcy()%n+1;
        if(l>r) swap(l,r);
        if(type==1)
        {
            x=wcy()%n+1;
            printf("%d %d %d %d\n",type,l,r,x);
        }
        else printf("%d %d %d\n",type,l,r);
    }
    return 0;
}