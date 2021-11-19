#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,x,a[MAXN];
vector<int> G[MAXN];
bool valid[MAXN];
vector<int> good;
void bfs()
{
    queue<int> que;
    for(int i=1;i<=n;i++) if(valid[i]) que.push(i);
    while(que.size())
    {
        int v=que.front(); que.pop();
        for(auto to:G[v])
        {
            if(a[to]<x&&!valid[to])
            {
                que.push(to);
                valid[to]=true;
            }
        }
    }
}
void extend()
{
    good.clear();
    for(int i=1;i<=n;i++) if(valid[i]) good.push_back(i);
    for(auto x:good)
        for(auto to:G[x])
            valid[to]=true;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    scanf("%d",&x);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    if(a[1]>=x) x/=2;
    valid[1]=true; 
    while(x>=1)
    {
        bfs();
        if(valid[n]) {printf("%d\n",x); return 0;}
        extend();
        x/=2;
    }
    puts("0");
    return 0;
}