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

const int maxn = 2e5 + 233;

int in[2 * maxn], out[2 * maxn], dfs_clock;
struct SAM{
#define sigma_size 26

    int len[maxn];
    int f[maxn];
    int cnt[maxn];
    int ch[maxn][sigma_size]; 
    int sz;
    int last;
    vector<int> G[maxn];

    void init() {  
        last = sz = 1; 
        f[1] = len[1] = 0;
        memset(ch[1], 0, sizeof(ch[1]));
    }

    void add(int c) {
        if(ch[last][c] && len[ch[last][c]] == len[last] + 1) {
            last = ch[last][c];
            return;
        }
        bool ok = 0;
        int x = ++sz; 
        len[x] = len[last] + 1; 
        int p; 
        for (p = last; p && !ch[p][c]; p = f[p])ch[p][c] = x;
        if (!p)f[x] = 1, cnt[1]++; 
        else {
            int q = ch[p][c];
            if(len[x] == len[p] + 1) ok = 1;
            if (len[p] + 1 == len[q])  
                f[x] = q, cnt[q]++; 
            else {
                int nq = ++sz;
                len[nq] = len[p] + 1;
                f[nq] = f[q];
                memcpy(ch[nq], ch[q], sizeof(ch[q]));
                for (; p && ch[p][c] == q; p = f[p])
                    ch[p][c] = nq;
                f[q] = f[x] = nq;
                cnt[nq] += 2;
                if(ok) last = nq;
                else last = x;
                return;
            }
        }
        last = x;
    }

    void build() {
        for (int i = 2; i <= sz; i += 1) {
            G[f[i]].emplace_back(i);
        }
        dfs(1);
    }
    void dfs(int u) {
        in[u] = ++dfs_clock;
        for (auto v : G[u]) {
            dfs(v);
        }
        out[u] = dfs_clock;
    }
}sam;

vector<pair<int, int> > G[maxn];
int n, m, q;

int d[maxn];
int cnt[maxn];
int mx_dep;
int fa[maxn][25];
int edge[maxn];

void dfs(int u, int f) {
    d[u] = d[f] + 1;
    mx_dep = max(mx_dep, d[u]);
    cnt[d[u]] += 1;
    fa[u][0] = f;
    for (int i = 1; i <= 20; i += 1) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for (auto [v, w] : G[u]) {
        if(v == f) continue;
        edge[v] = w;
        dfs(v, u);
    }
}

int lca(int x, int y) {
    if(d[x] > d[y]) swap(x, y);
    for (int i = 20; i >= 0; i -= 1) {
        if(d[x] <= d[fa[y][i]]) y = fa[y][i];
    }
    if(x == y) return x;
    for (int i = 20; i >= 0; i -= 1) {
        if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    }
    return fa[x][0];
}

const int N = 350;

bool good[maxn];
int good_sz;
int up[350][100005];
int down[350][100005];

int up_first[maxn];
int id[maxn];

void dfs1(int u, int pre) {
    up_first[u] = pre;
    if(good[u] && pre) {
        good_sz += 1;
        id[u] = good_sz;
        for (int i = 1; i <= sam.sz; i += 1) {
            int cur = i;
            int p = u;
            while(p != pre) {
                cur = sam.ch[cur][edge[p]];
                if(!cur) cur = 1;
                p = fa[p][0];
            }
            up[good_sz][i] = cur;
        }
        int p = u;
        vector<int> lst;
        while(p != pre) {
            lst.emplace_back(edge[p]);
            p = fa[p][0];
        }
        reverse(lst.begin(), lst.end());
        for (int i = 1; i <= sam.sz; i += 1) {
            
            int cur = i;
            for (auto v : lst) {
                cur = sam.ch[cur][v];
                if(!cur) cur = 1;
            }
            
            down[good_sz][i] = cur;
            
        }
    }
    for (auto [v, w] : G[u]) {
        if(v == fa[u][0]) continue;
        dfs1(v, good[u] ? u : pre);
    }
}

int find_where(int u, int v) {
    int lc = lca(u, v);
    int cur = 1;

    while(u && !good[u] && u != lc) {
        cur = sam.ch[cur][edge[u]];
        if(!cur) cur = 1;
        u = fa[u][0];
    }
    while(d[up_first[u]] >= d[lc]) {
        cur = up[id[u]][cur];
        u = up_first[u];
    }
    while(u != lc) {
        cur = sam.ch[cur][edge[u]];
        if(!cur) cur = 1;
        u = fa[u][0];
    }

    {
        vector<int> lst;
        int p = v;
        while(d[up_first[p]] >= d[lc]) {
            lst.emplace_back(up_first[p]);
            p = up_first[p];
        }

        reverse(lst.begin(), lst.end());

        vector<int> path;
        int first;
        if(lst.empty()) {
            first = v;
        }
        else first = lst[0];
        while(first != lc) {
            path.emplace_back(edge[first]);
            first = fa[first][0];
        }
        reverse(path.begin(), path.end());
        for (auto v : path) {
            cur = sam.ch[cur][v];
            if(!cur) cur = 1;
        }
        if(lst.empty()) {
            return cur;
        }
        for (int i = 1; i < lst.size(); i += 1) {
            cur = down[id[lst[i]]][cur];
        }
        path.clear();
        first = v;
        while(first != lst.back()) {
            path.emplace_back(edge[first]);
            first = fa[first][0];
        }
        reverse(path.begin(), path.end());
        for (auto v : path) {
            cur = sam.ch[cur][v];
            if(!cur) cur = 1; 
        }
        return cur;
    }
}

int test(string x) {
    int cur = 1;
    for (int i = 0; x[i]; i += 1) {
        cur = sam.ch[cur][x[i] - 'a'];
        if(!cur) cur = 1;
    }
    return cur;
}

string str[maxn];
int c[2 * maxn];

int lowbit(int x) {
    return x & (-x);
}

void upd(int x, int d) {
    while(x <= sam.sz) {
        c[x] += d;
        x += lowbit(x);
    }
}

int query(int x) {
    int ret = 0;
    while(x) {
        ret += c[x];
        x -= lowbit(x);
    }
    return ret;
}

vector<tuple<int, int, int, int> > ask[maxn];
using ll = long long;
ll res[maxn];

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    sam.init();
    cin >> n >> m >> q;
    for (int i = 1; i < n; i += 1) {
        int u, v;
        string s;
        cin >> u >> v >> s;
        G[u].emplace_back(v, s[0] - 'a');
        G[v].emplace_back(u, s[0] - 'a');
    }

    for (int i = 1; i <= m; i += 1) {
        string s;
        cin >> s;
        str[i] = s;
        sam.last = 1;
        for (int j = 0; s[j]; j += 1) {
            sam.add(s[j] - 'a');
        }
    }
    sam.build();
    for (int i = 1; i <= q; i += 1) {
        int u, v, l, r;
        cin >> u >> v >> l >> r;
        ask[l - 1].emplace_back(u, v, -1, i);
        ask[r].emplace_back(u, v, 1, i);
    }

    dfs(1, 0);
    {
        int mn = 0;
        cnt[0] = 1e9;
        vector<int> lst;
        for (int i = 1; i <= mx_dep; i += 1) {
            if(cnt[mn] > cnt[i]) mn = i;
            if(i % N == 0) {
                lst.emplace_back(mn);
                mn = 0;
            }
        }
        for (int i = 1; i <= n; i += 1) {
            if(binary_search(lst.begin(), lst.end(), d[i])) {
                good[i] = 1;
            }
        }
    }
    dfs1(1, 0);
    
    for (int i = 1; i <= m; i += 1) {
        string s = str[i];
        int cur = 1;
        for (int j = 0; s[j]; j += 1) {
            cur = sam.ch[cur][s[j] - 'a'];
            //debug(in[cur], 1);
            upd(in[cur], 1);
        }
        for (auto [u, v, c, id] : ask[i]) {
            int cur = find_where(u, v);
          //  debug(cur, out[cur], in[cur]);
            res[id] += c * (query(out[cur]) - query(in[cur] - 1)); 
        }
    }
    for (int i = 1; i <= q; i += 1){
        cout << res[i] << "\n";
    }
    return 0;
}

/*

2 5 3 
1 2 a 
aab abab aaa b a 
2 1 1 5 
1 2 1 3 
2 1 3 5

9 5 6 
1 2 a 
2 7 c 
1 3 b 
3 4 b 
4 6 b 
3 5 a 
5 8 b 
5 9 c 
aaaaaaabbbbbbaaaabbbb
abababababababab
abaaabbabababa
abbbbabaaaabb
abababab

9 5 6 
1 2 a 
2 7 c 
1 3 b 
3 4 b 
4 6 b 
3 5 a 
5 8 b 
5 9 c 
ababa 
cabbb 
bac 
bbbac 
abacaba 
2 7 1 4 
2 5 1 5 
6 3 4 4 
6 9 4 5 
5 7 3 5 
5 3 1 5
*/