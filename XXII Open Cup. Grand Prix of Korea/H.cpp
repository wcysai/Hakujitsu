#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 233;
using ll = long long;
vector<pair<int, int> > G[maxn];
int value[maxn];
int n, m;
ll t;

ll dis[maxn];
int res[maxn];

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m >> t;
    for (int i = 0; i < m; i += 1) {
        int x, y;
        cin >> x >> y;
        G[y].emplace_back(x, i);
    }
    for (int i = 1; i <= n; i += 1) {
        cin >> value[i];
    }
    for (int bit = 0; bit < 8; bit += 1) {
        priority_queue<pair<ll, int> > q;
        for (int i = 1; i <= n; i += 1) {
            dis[i] = 2e18;
            if(value[i] >> bit & 1) {
                dis[i] = 0;
                q.emplace(0, i);
            }
        }
        while(!q.empty()) {
            auto [d, u] = q.top();
            d = -d;
            q.pop();
            if(d > dis[u]) continue;
            dis[u] = d;
            for (auto [v, id] : G[u]) {
                ll cur = (dis[u] % m <= id ? dis[u] / m * m + id + 1 : dis[u] / m * m + id + 1 + m);
                if(dis[v] > cur) {
                    dis[v] = cur;
                    q.emplace(-cur, v);
                }
            }
        }
        for (int i = 1; i <= n; i += 1) {
            //cerr << bit << " " << i << " " << dis[i] << endl;
            if(dis[i] <= t) res[i] += 1 << bit;
        }
    }
    for(int i = 1; i <= n; i += 1) {
        cout << res[i] << " \n"[i == n];
    }
    return 0;
}

/*
5 4 5
1 2
2 3
2 4
4 4
8 0 5 3 10
*/