#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int maxn = 4e5 + 233;
int ord[maxn];
bool vis[maxn];
vector<int> G[maxn];
int x[maxn], y[maxn];
int n, m;

using ll = long long;

ll cross(int x1, int y1, int x2, int y2){
    return 1ll * x1 * y2 - 1ll * y1 * x2;
}

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i += 1) {
        cin >> x[i] >> y[i];
    }
    for (int i = 1; i <= m; i += 1){
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    if(m != 3 * n - 6) {
        cout << "NO\n";
        return 0;
    }
    for (int i = 1; i <= n; i += 1) {
        sort(G[i].begin(), G[i].end());
        ord[i] = i;
    }
    sort(ord + 1, ord + n + 1, [&](int a, int b){
        if(x[a] != x[b]) return x[a] < x[b];
        return y[a] < y[b];
    });
    bool flag = true;
    for (int o = 1; o <= n; o += 1) {
        int i = ord[o];
        vis[i] = 1;
        vector<int> lst;
        for (auto x : G[i]) {
            if(!vis[x]) lst.emplace_back(x); 
        }
        sort(lst.begin(), lst.end(), [&](int a, int b){
            return cross(x[a] - x[i], y[a] - y[i], x[b] - x[i], y[b] - y[i]) > 0;
        });
        for (int j = 1; j < lst.size(); j += 1) {
            int cur = lst[j - 1];
            flag &= binary_search(G[cur].begin(), G[cur].end(), lst[j]);
        }
        if(!flag) break;
    }
    cout << (flag ? "YES" : "NO") << "\n";
    return 0;
}

/*
3 3
0 0
1 0
0 1
1 2
2 3
3 1

4 4
0 0
3 0
0 3
1 1
1 2
2 3
3 1
1 4

4 6
0 0
3 0
0 3
1 1
1 2
2 3
3 1
1 4
2 4
3 4

4 5
0 0
2 0
1 1
0 2
1 2
1 3
1 4
2 3
3 4

4 3
0 0
0 1
1 1
1 2
1 2
2 3
3 4

5 8

*/