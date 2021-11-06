#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
char str[MAXN];
int p[MAXN],r[MAXN],l[MAXN],r[MAXN];
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        r[i]=0;
    }
}
int find(int x)
{
    if(p[x]==x) return x;
    return p[x]=find(p[x]);
}
void unite(int u,int v)
{
    u=find(u); v=find(v);
    if(u==v) return;
    if(r[u]<r[v]) p[u]=v;
    else
    {
        p[v]=u;
        if(r[u]==r[v]) r[u]++;
    }
}
struct segtree
{
    int sum[4*MAXN];
    void 
};
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%s",str+1);
    for(int i=0;i<m;i++) scanf("%d%d",&l[i],&r[i]);
    return 0;
}