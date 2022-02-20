#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
using namespace std;

void debug_out() {cerr << endl;}
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T)
{
    cerr << " " << H;
    debug_out(T...);
}
#ifndef ONLINE_JUDGE
    #define debug(...) cerr << "{" << #__VA_ARGS__ << "}:", debug_out(__VA_ARGS__)
#else
    #define debug(...) 42
#endif

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vp;
const int inf = 1e9;
const ll INF = 1e18;
const db eps = 1e-10;
const db pi = acos(-1);

#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define ep emplace
#define mem(a) memset(a, 0, sizeof(a))
#define copy(a, b) memcpy(a, b, sizeof(b))
#define PA cout << "pass\n"
#define lowbit(x) (x & -x)
#define all(x) x.begin(), x.end()
#define TM cout << db(clock()) / CLOCKS_PER_SEC << '\n'

mt19937 mrand(chrono::high_resolution_clock::now().time_since_epoch().count());

template<class T>inline void upmin(T &x, T y) {x = x > y ? y : x;}
template<class T>inline void upmax(T &x, T y) {x = x < y ? y : x;}

const int maxn = 2e5 + 233;
int f[maxn][25], par[maxn], son[maxn], sz[maxn] , rt, tot, n;

vi G[maxn];
bool vis[maxn];
using ui = unsigned int;

ui res;
ui d[maxn];
vector<int> g[maxn];

/*
struct BIT {
    ui c[maxn];
    void upd(int x, ui d) {
        while (x <= n) {
            c[x] += d;
            x += lowbit(x);
        }
    }

    ui query(int x) {
        ui ret = 0;
        while (x) {
            ret += c[x];
            x -= lowbit(x);
        }
        return ret;
    }
}tr1, tr2, tr3, tr4;
*/
ui tr1[maxn], tr2[maxn], tr3[maxn], tr4[maxn];

void dfs(int u, int fa) {
    d[u] = d[fa] + 1;
    f[u][0] = fa;
    for(int i = 1; i <= 20; i++) f[u][i] = f[f[u][i - 1]][i - 1];
    for (auto v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
}

int lca(int x, int y){
    if(d[x] > d[y]) swap(x, y);
    for(int i = 20; i >= 0; i--){
        if(d[f[y][i]] >= d[x]) y = f[y][i];
    }
    if(x == y) return x;
    for(int i = 20; i >= 0; i--){
        if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    }
    return f[x][0];
}

ui getdis(int x, int y){
    int lc = lca(x, y);
    return d[x] + d[y] - 2 * d[lc];
}


void getroot(int u, int fa){
    sz[u] = 1;
    son[u] = 0;
    for(auto v : G[u]){
        if(v == fa || vis[v]) continue;
        getroot(v, u);
        sz[u] += sz[v];
        upmax(son[u], sz[v]);
    }
    upmax(son[u], tot - sz[u]);
    if(son[u] < son[rt]) rt = u;
}


void solve(int u){
    vis[u] = 1;
    for(auto v : G[u]){
        if(vis[v]) continue;
        tot = sz[v];
        rt = 0;
        getroot(v, 0);
        par[rt] = u;
        solve(rt);
    }
}

namespace LCA{
    int vs[maxn*2-1];
    int depth[maxn*2-1];
    int id[maxn];
    int st[22+1][2*maxn];
    
    void dfs(int v,int p,int d,int &k){
        id[v]=k;
        vs[k]=v;
        depth[k++]=d;
        for(int i=0;i<(int)G[v].size();i++)
        {
            if(G[v][i]!=p)
            {
                dfs(G[v][i],v,d+1,k);
                vs[k]=v;
                depth[k++]=d;
            }
        }
    }
    int getMin(int x, int y)
    {
        return depth[x]<depth[y]?x:y;
    }

    void rmq_init(int n)
    {
        for(int i=1;i<=n;++i) st[0][i]=i;
        for(int i=1;1<<i<n;++i)
            for(int j=1;j+(1<<i)-1<=n;++j)
                st[i][j]=getMin(st[i-1][j],st[i-1][j+(1<<(i-1))]);
    }
    void init(int V)
    {
        int k=0;
        dfs(1,0,0,k);
        rmq_init(V*2-1);
    }
    int query(int l, int r)
    {
        int k=31-__builtin_clz(r-l+1);
        return getMin(st[k][l],st[k][r-(1<<k)+1]);
    }
    int lca(int u,int v)
    {
        if(u==v) return u;
        return vs[query(min(id[u],id[v]),max(id[u],id[v]))];
    }
    int dis(int u,int v)
    {
        return depth[id[u]]+depth[id[v]]-2*depth[id[lca(u,v)]];
    }
};


void insert(int u, int c){
    //tr1.upd(u, 0);
 //   tr2.upd(u, 1);
    tr2[u] += c;
    int p = u;
    while(par[p]){
        ui dis = LCA::dis(par[p], u);
        /*
        tr1.upd(par[p], dis);
        tr2.upd(par[p], 1);
        dis = getdis(p, u);
        tr3.upd(p, dis);
        tr4.upd(p, 1);
        */
        
        tr1[par[p]] += dis * c;
        tr2[par[p]] += c;
        tr3[p] += dis * c;
        tr4[p] += c;
        p = par[p];
    }
}

ui cal(int u){
    int p = u;
    ui sum = tr1[u];
    //debug(u, tr1.query(u));
    while(par[p]){
        ui dis = LCA::dis(par[p], u);
        
        ui c = tr2[par[p]];
        sum += tr1[par[p]] + c * dis;
        c = tr4[p];
        sum -= tr3[p] + c * dis;
        //debug(sum, tr3.query(p), c, dis);
        /*
        if(dis <= k) {
            sum += tr1.query(par[p], k - dis);
            sum -= tr2.query(p, k - dis);
        }
        */
        p = par[p];
    }
    return sum;
}

int cnt[maxn];
int go[maxn];
ui cur;
ui tot_len[maxn];
ui ans;

void prepare(int u, int fa){
    cnt[u] = 1;
    for(auto v : g[u]){
        if(v == fa) continue;
        prepare(v, u);
        cnt[u] += cnt[v];
        if(cnt[go[u]] < cnt[v]) go[u] = v;
    }
}

void clean(int u, int fa) {
    insert(u, -1);
    cur -= tot_len[u] - 2 * cal(u);
    for (auto v : g[u]) {
        if(v == fa) continue;
        clean(v, u);
    }
}

bool is_cal[maxn];

void dsu_on_tree(int u, int fa, bool ok) {
    for (auto v : g[u]) {
        if(v == fa || v == go[u]) continue;
        dsu_on_tree(v, u, 0);
    } 
    if(go[u]) dsu_on_tree(go[u], u, 1);
    for (auto v : g[u]) {
        if(v == fa || v == go[u]) continue;
        dsu_on_tree(v, u, 1);
    }  
    
    cur += tot_len[u] - 2 * cal(u);
    if(!is_cal[u] && u != 1) {
        is_cal[u] = 1;
        res += cur;
        //debug(u, cur);
    }
    insert(u, 1);
    if(!ok) clean(u, fa);
}

ui fuck() {
    res = 0;
    for (int i = 0; i <= n; i += 1){
        tr1[i] = tr2[i] = tr3[i] = tr4[i] = vis[i] = par[i] = son[i] = 0;
        memset(f[i], 0, sizeof(f[i]));
        is_cal[i] = 0;
        cnt[i] = tot_len[i] = go[i] = sz[i] = d[i] = 0;
    }
    LCA::init(n);
    cur = 0;
    son[0] = 1e9;
    tot = n;
    rt = 0;
    prepare(1, 0);
    dfs(1, 0);
    getroot(1, 0);
    solve(rt);
    for (int i = 1; i <= n; i += 1){
        insert(i, 1);
    }
    for (int i = 1; i <= n; i += 1){
        tot_len[i] = cal(i);
    }
    for (int i = 1; i <= n; i += 1){
        insert(i, -1);
    }
    dsu_on_tree(1, 0, 1);
    return res;
}

vector<int> G1[maxn], G2[maxn];

int main() {

    freopen("A.in","r",stdin);
    clock_t startTime,endTime;
      startTime = clock();
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i < n; i += 1){
        int u, v;
        cin >> u >> v;
        G1[u].emplace_back(v);
        G1[v].emplace_back(u);
    }
    for (int i = 1; i < n; i += 1){
        int u, v;
        cin >> u >> v;
        G2[u].emplace_back(v);
        G2[v].emplace_back(u);
    }
    
    for (int i = 1; i <= n; i += 1){
        G[i] = G1[i];
        g[i] = G1[i];
    }
    ans += fuck();
    
    for (int i = 1; i <= n; i += 1){
        G[i] = G2[i];
        g[i] = G2[i];
    }
    ans += fuck();
    
    for (int i = 1; i <= n; i += 1){
        G[i] = G1[i];
        g[i] = G2[i];
    }
    
    ans += 2 * fuck();
    
    cout << ans << "\n";
    endTime = clock();//计时结束
     cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    return 0;
}