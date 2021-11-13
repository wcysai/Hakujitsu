#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 3005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,tot,u[MAXN],v[MAXN];
int p2[MAXN],ans[MAXN];
vector<int> G[MAXN];
vector<int> cnt[MAXN];
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
void dfs(int v,int p,int d,int save)
{
    while(cnt[save].size()<=d-1) cnt[save].push_back(0); 
    cnt[save][d-1]++;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v,d+1,save);
    }
}
int main()
{
    p2[0]=1;
    for(int i=1;i<=3000;i++) p2[i]=2LL*p2[i-1]%MOD;
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        scanf("%d%d",&u[i],&v[i]);
        add_edge(u[i],v[i]);
    }
    ans[0]=n;
    for(int v=1;v<=n;v++) //vertex as center
    {
        int maxi=0;
        for(auto to:G[v]) 
        {
            dfs(to,v,1,to);
            maxi=max(maxi,(int)cnt[to].size());
        }
        int s=1;
        for(int i=1;i<=maxi;i++)
        {
            int c=0,res=0;
            for(auto to:G[v]) 
            {
                int cc=(cnt[to].size()>=i?cnt[to][i-1]:0);
                c+=cc;
                add(res,p2[cc]-1);
            }
            int tmp=p2[c]; dec(tmp,res); dec(tmp,1);
            add(ans[i*2],1LL*tmp*p2[s]%MOD);
            s+=c;
        }
        for(auto to:G[v]) cnt[to].clear();
    }
    for(int id=0;id<n-1;id++) //edge as center
    {
        int maxi=0;
        dfs(u[id],v[id],1,u[id]); maxi=max(maxi,(int)cnt[u[id]].size());
        dfs(v[id],u[id],1,v[id]); maxi=max(maxi,(int)cnt[v[id]].size());
        vector<int> vt; vt.push_back(u[id]); vt.push_back(v[id]);
        int s=0;
        for(int i=1;i<=maxi;i++)
        {
            int c=0,res=0;
            for(auto to:vt) 
            {
                int cc=(cnt[to].size()>=i?cnt[to][i-1]:0);
                c+=cc;
                add(res,p2[cc]-1);
            }
            int tmp=p2[c]; dec(tmp,res); dec(tmp,1);
            add(ans[i*2-1],1LL*tmp*p2[s]%MOD);
            s+=c;
        }
        cnt[u[id]].clear(); cnt[v[id]].clear();
    }
    for(int i=0;i<=n-1;i++) printf("%d ",ans[i]);
    puts("");
    return 0;
}