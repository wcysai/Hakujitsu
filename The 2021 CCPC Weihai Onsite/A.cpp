#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,deg[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        deg[u]++; deg[v]++;
    }
    bool f=true; int cnt=0;
    for(int i=1;i<=n;i++) 
    {
        if(deg[i]>=4) f=false;
        else if(deg[i]==3) cnt++;
    }
    if(!f) puts("0"); else printf("%d\n",n-cnt);
    return 0;
}