#include <bits/stdc++.h>
using namespace std;

typedef double db;

int n, t, r, m, k;
const int inf = 1e9;

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> t >> r;
    cin >> n >> m;
    vector<pair<int, int> > G[n + 1];
    for (int i = 1; i <= m; i += 1) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }

    auto solve = [&](int s) {
        vector<int> dis(n + 1, inf);
        dis[s] = 0;
        priority_queue<pair<int, int> > pq;
        pq.emplace(0, s);
        while(!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            d = -d;
            if(dis[u] < d) continue;
            for (auto [v, w] : G[u]) {
                if(dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    pq.emplace(-dis[v], v);
                }
            }
        }
        return dis;
    };

    auto S = solve(1);
    auto E = solve(n);

    cin >> k;
    vector<int> go[k];
    vector<int> key_pos(k);
    vector<db> prob(k);

    
    for (int i = 0; i < k; i += 1) {
        cin >> key_pos[i] >> prob[i];
        go[i] = solve(key_pos[i]);
        prob[i] = 1.0 * prob[i] / 100;
    }

    if(S[n] == inf) {
        cout << "-1\n";
        return 0;
    }
    vector<vector<db> > dp(k, vector<db>(1 << k, 1e18));
    int all = (1 << k) - 1;
    
    for (int i = 0; i < k; i += 1) {
        if(E[key_pos[i]] == inf) continue;
        dp[i][all] = 1.0 * E[key_pos[i]] / t;
    }

    auto upd = [&](db &x, db y) {
        x = min(x, y);
    };

   
    for (int mask = all; mask; mask -= 1) {
        for (int i = 0; i < k; i += 1) {
            if(!(mask >> i & 1)) continue;
            if(E[key_pos[i]] < inf) upd(dp[i][mask], 1.0 * E[key_pos[i]] / t);
            for (int j = 0; j < k; j += 1) {
                if(go[j][key_pos[i]] == inf) continue;
                if(E[key_pos[j]] == inf) continue;
                if(!(mask >> j & 1)) {
                    upd(dp[i][mask], 
                    dp[j][mask ^ (1 << j)] * prob[j] + E[key_pos[j]] * (1 - prob[j]) / r + 1.0 * go[i][key_pos[j]] / t);
                }
            } 
        }
    }

    double res = S[n] == inf ? 1e18 : 1.0 * S[n] / t; 
    for (int i = 0; i < k; i += 1) {
        if(S[key_pos[i]] == inf) continue;
        if(E[key_pos[i]] == inf) continue;
        res = min(res, 1.0 * S[key_pos[i]] / t + prob[i] * dp[i][1 << i] + (1. - prob[i]) * E[key_pos[i]] / r);
    }
    cout << fixed << setprecision(15) << res << "\n";
    return 0;
}

/*
3 15
4 3
1 2 600
1 3 300
2 4 900
1
3 50

3 15
5 4
1 2 600
1 3 300
4 5 900
3 2 300
2
3 50
4 0

1.0 * prob[i] * E[key_pos[i]] / r
*/