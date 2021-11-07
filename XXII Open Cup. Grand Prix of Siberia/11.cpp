#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,f[MAXN],g[MAXN],x,y;
vector<int> occf[MAXN],occg[MAXN];
ll ans;
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&f[i]);
    for(int i=1;i<=n;i++) scanf("%d",&g[i]);
    scanf("%d%d",&x,&y);
    int t=0;
    while(true)
    {
        if(occf[x].size()==2) break;
        occf[x].push_back(t);
        t++; x=f[x];
    }
    t=0;
    while(true)
    {
        if(occf[y].size()==2) break;
        occf[y].push_back(t);
        t++; y=g[y];
    }
    ll ans=INF;
    for(int i=1;)
    return 0;
}