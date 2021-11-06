#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int a[MAXN][MAXN];
int b[MAXN][MAXN];
int c,same[MAXN];
bool vis[MAXN];
vector<string> v;
void dfs(int v)
{
    vis[v]=true; c++;
    for(int i=1;i<=n;i++)
    {
        if(v==i||vis[i]||!b[v][i]) continue;
        dfs(i);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        a[u][v]=a[v][u]=1;
    }
    for(int leaf=1;leaf<=n;leaf++)
    {
        for(int par=1;par<=n;par++)
        {
            if(par==leaf) continue;
            memset(same,0,sizeof(same));
            same[leaf]=1;
            if(a[par][leaf]) same[par]=1; 
            for(int i=1;i<=n;i++)
            {
                if(i==par||i==leaf) continue;
                if(!a[leaf][i]) same[i]=1;
            }
            int cnt=0;
            memset(b,0,sizeof(b));
            for(int i=1;i<=n;i++)
            {
                if(cnt>n-1) break;
                for(int j=i+1;j<=n;j++)
                {
                    b[i][j]=b[j][i]=(a[i][j]^same[i]^same[j]);
                    if(b[i][j]) cnt++;
                }
            }
            if(cnt==n-1)
            {
                c=0;
                memset(vis,false,sizeof(vis));
                dfs(1);
                if(c==n)
                {
                    string str="";
                    int val=same[1]^1;
                    for(int i=1;i<=n;i++) if(same[i]^val) str+='0'; else str+='1';
                    v.push_back(str); 
                }
            }
        }
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    printf("%d\n",2*v.size());
    return 0;
}