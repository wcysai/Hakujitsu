#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
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

typedef long double db;
const int maxn = 2e6 + 233;

db c[maxn];
int n, S, m;
vector<int> G[maxn];

int bfs_clock;
int bfn[maxn], rk[maxn];
int f[maxn];
int l[maxn], r[maxn];

int lowbit(int x) {
    return x & (-x);
}

void upd(int x, double d) {
    while(x <= n + 5) {
        c[x] += d;
        x += lowbit(x);
    }
}

db query(int x) {
    db ret = 0;
    while(x) {
        ret += c[x];
        x -= lowbit(x);
    }
    return ret;
}

void dfs(int u, int fa){ 
    f[u] = fa;
    l[u] = bfs_clock + 1;
    for (auto v : G[u]) {
        if(v == fa) continue;
        bfn[++bfs_clock] = v;
        rk[v] = bfs_clock;
    }
    r[u] = bfs_clock;
    for (auto v : G[u]) {
        if(v == fa) continue;
        dfs(v, u);
    }
}

void range_upd(int l, int r, db x) {
    upd(l, x);
    upd(r + 1, -x);
}

int T;

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d", &n, &S);
        for (int i = 0; i <= n + 5; i += 1) {
            G[i].clear();
            c[i] = 0;
        }
        for (int i = 1; i < n; i += 1) {
            int u, v;
            scanf("%d %d", &u, &v);
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        bfs_clock = 1;
        bfn[1] = 1;
        rk[1] = 1;
        dfs(1, 0);
        range_upd(rk[S], rk[S], 1);
        db res = 0;
        scanf("%d", &m);
        while(m--) {
            int x;
            scanf("%d", &x);
            db tmp = query(rk[x]);
            //debug(x, tmp);
            res += tmp;
            int son = G[x].size();
            range_upd(l[x], r[x], tmp / son);
            if(f[x]) {
                range_upd(rk[f[x]], rk[f[x]], tmp / son);
            }
            range_upd(rk[x], rk[x], -tmp);
        }
        printf("%.15f\n", double(res));
    }
    return 0;
}

/*
1 
4 2 
1 2 
2 3 
4 2 
4
1 2 3 2
*/
