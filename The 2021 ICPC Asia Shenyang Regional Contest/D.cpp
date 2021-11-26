#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 233;
const int inf = 1e9;
vector<int> G[maxn];

struct edge{
    int from, to, cap, flow;
};

vector<edge> edges;
bool vis[maxn];
int d[maxn];
int cur[maxn];
int s, t, tot;

void init(){
    edges.clear();
    for (int i = 0; i <= t; i += 1) {
        G[i].clear();
    }
}

void addedge(int from, int to, int cap) {
    edges.push_back(edge{from, to, cap, 0});
    edges.push_back(edge{to, from, 0, 0});
    tot = edges.size();
    G[from].emplace_back(tot - 2);
    G[to].emplace_back(tot - 1);
}

bool bfs(){
    for (int i = 0; i <= t; i += 1) {
        vis[i] = 0;
    }
    queue<int> q;
    q.emplace(s);
    d[s] = 0;
    vis[s] = 1;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < G[x].size(); i += 1) {
            edge &e = edges[G[x][i]];
            if(!vis[e.to] && e.cap > e.flow) {
                vis[e.to] = 1;
                d[e.to] = d[x] + 1;
                q.emplace(e.to);
            }
        }
    }
    return vis[t];
}

int dfs(int x, int a) {
    if(x == t || a == 0) return a;
    int flow = 0, f;
    for (int &i = cur[x]; i < G[x].size(); i += 1) {
        edge &e = edges[G[x][i]];
        if(d[x] + 1 == d[e.to] && (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
            e.flow += f;
            edges[G[x][i] ^ 1].flow -= f;
            flow += f;
            a -= f;
            if(a == 0) break;
        }
    }
    return flow;
}

int maxflow(){
    int flow = 0;
    while(bfs()) {
        for (int i = 0; i <= t; i += 1) {
            cur[i] = 0;
        }
        flow += dfs(s, inf);
    }
    return flow;
}

int w, h, n;
int sx[maxn], sy[maxn], ex[maxn], ey[maxn];
int dx[5] = {1, -1, 0, 0, 0};
int dy[5] = {0, 0, 1, -1, 0};

int id(int t, int x, int y) {
    return t * w * h + (x - 1) * h + y;
}

bool in(int x, int y) {
    return x >= 1 && x <= w && y >= 1 && y <= h;
}

char path(int x1, int y1, int x2, int y2) {
    int xx = x2 - x1;
    int yy = y2 - y1;
    if(xx == 0 && yy == 0) return 'S';
    if(xx == 1 && yy == 0) return 'D';
    if(xx == -1 && yy == 0) return 'U';
    if(xx == 0 && yy == 1) return 'R';
    if(xx == 0 && yy == -1) return 'L';
    assert(0);
}

vector<pair<int, int> > lst;

void solve(int u, bool ok) {
    int cur = (u - 1) % (w * h) + 1;
    if(ok) lst.emplace_back((cur - 1) / h + 1, (cur - 1) % h + 1);
    for (int i = 0; i < G[u].size(); i += 1) {
        edge &e = edges[G[u][i]];
        if(e.flow > 0) {
            e.flow = 0;
            solve(e.to, !ok);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> w >> h;
    for (int i = 1; i <= n; i += 1) {
        cin >> sx[i] >> sy[i];
    }
    for (int i = 1; i <= n; i += 1) {
        cin >> ex[i] >> ey[i];
    }
    int lo = 1, hi = 2 * (w + h), ans = -1;

    auto check = [&](int mid){
        init();
        s = 0;
        t = 2 * id(mid, w, h) + n + 1;
        for (int i = 1; i <= mid; i += 1) {
            for (int x = 1; x <= w; x += 1) {
                for(int y = 1; y <= h; y += 1) {
                    addedge(id(2 * i - 2, x, y), id(2 * i - 1, x, y), 1);
                }
            }
        }
        for (int i = 1; i <= n; i += 1) {
            addedge(s, id(0, sx[i], sy[i]), 1);
        }
        for (int i = 2; i <= mid; i += 1) {
            for (int x = 1; x <= w; x += 1) {
                for (int y = 1; y <= h; y += 1) {
                    for (int k = 0; k < 5; k += 1) {
                        if(!in(x + dx[k], y + dy[k])) continue;
                        addedge(id(2 * (i - 1) - 1, x, y), id(2 * (i - 1), x + dx[k], y + dy[k]), 1);
                    }
                }
            }
        }
        for (int i = 1; i <= mid; i += 1) {
            for (int j = 1; j <= n; j += 1) {
                addedge(id(2 * i - 1, ex[j], ey[j]), id(2 * mid, 1, j), 1);
            }
        }
        for (int i = 1; i <= n; i += 1) {
            addedge(id(2 * mid, 1, i), t, 1);
        }
        
        int flow = maxflow();
        return flow == n;
    };

    while(hi >= lo) {
        int mid = lo + hi >> 1;
        if(check(mid)) {
            hi = mid - 1;
            ans = mid;
        }
        else lo = mid + 1;
    }

    check(ans);
    cout << ans - 1 << "\n";
    for (int i = 1; i <= n; i += 1) {
        lst.clear();
        solve(id(0, sx[i], sy[i]), 1);
        lst.pop_back();
        cout << sx[i] << " " << sy[i] << " " << lst.back().first << " " << lst.back().second << " ";
        int len = 0;
        for (int j = 1; j < lst.size(); j += 1) {
            auto [x1, y1] = lst[j - 1];
            auto [x2, y2] = lst[j];
            len += 1;
            cout << path(x1, y1, x2, y2);
        }
        if(len == ans - 1) {
            cout << "\n";
            continue;
        }
        else{
            while(len < ans - 1) {
                len += 1;
                cout << "P";
            }
            cout << "\n";
            continue;
        }
    }
    return 0;
}

/*
3 4 4
1 1
1 4
4 4
1 3
2 3
2 4

3 2 2
1 1
1 2
2 2
1 1
2 1
2 2

2 3 3
1 1
1 3
1 2
2 2
*/