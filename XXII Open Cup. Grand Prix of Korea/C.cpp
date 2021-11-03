#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
mt19937 wcy(time(NULL));
int d,n,t;
int p[MAXN],lab[MAXN],w[MAXN];
int MOD[2]={1000000007,1000000009};
int rng[2][MAXN];
P tmp[MAXN];
P hsh[MAXN];
map<P,int> mp;
map<int,int> mmp;
int get_id(P p,int now)
{
    if(mp.find(p)==mp.end()) mp[p]=now;
    return mp[p];
}
void gen()
{
    for(int i=0;i<2;i++)
        for(int j=0;j<2*n;j++)
            rng[i][j]=wcy()%MOD[i];
}
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        lab[i]=i;
    }
}
int find(int x)
{
    if(p[x]==x) return x;
    else return p[x]=find(p[x]);
}
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    p[x]=y; 
}
vector<vector<pair<int,P> > >G;//trees
vector<int> H[MAXN];
void dfs(int now,int d)
{
    tmp[now].F=tmp[now].S=1;
    for(auto to:H[now])
    {
        dfs(to,d+1);
        tmp[now].F=1LL*tmp[now].F*(tmp[to].F+rng[0][d])%MOD[0];
        tmp[now].S=1LL*tmp[now].S*(tmp[to].S+rng[1][d])%MOD[1];
    }
    tmp[now].F=(tmp[now].F+w[now])%MOD[0];
    tmp[now].S=(tmp[now].S+w[now])%MOD[1];
}
void construct_hash(int id)
{
    for(int i=1;i<=2*n-1;i++) H[i].clear();
    init(2*n-1);
    sort(G[id].begin(),G[id].end(),greater<pair<int,P> >());
    int tot=n;
    //canonical tree
    int last=0;
    set<int> s;
    for(auto tup:G[id])
    {
        int u=tup.S.F,v=tup.S.S,c=tup.F;
        if(last!=0&&c!=last)
        {
            set<int> ss; mp.clear();
            for(auto xx:s) ss.insert(find(xx));
            for(auto xx:ss) {mmp[xx]=++tot; w[tot]=last;}
            for(auto xx:s)
            {
                int fa=mmp[find(xx)];
                H[fa].push_back(lab[xx]);
                lab[xx]=fa;
            }
            s.clear();
        }
        u=find(u); v=find(v);
        s.insert(u); s.insert(v);
        unite(u,v);
        last=c;
    }
    set<int> ss; mp.clear();
    for(auto xx:s) ss.insert(find(xx));
    for(auto xx:ss) {mmp[xx]=++tot; w[tot]=last;}
    for(auto xx:s)
    {
        int fa=mmp[find(xx)];
        H[fa].push_back(lab[xx]);
    }
    dfs(tot,0);
    hsh[id]=tmp[tot];
}
int main()
{
    scanf("%d%d",&d,&n);
    gen();
    G.resize(d+1); 
    for(int i=1;i<=n;i++) w[i]=i;
    for(int i=1;i<=d;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            int u,v,c;
            scanf("%d%d%d",&u,&v,&c);
            G[i].push_back(make_pair(c,P(u,v)));
        }
        construct_hash(i);
    }
    for(int i=1;i<=d;i++) printf("%d ",get_id(hsh[i],i));
    return 0;
}