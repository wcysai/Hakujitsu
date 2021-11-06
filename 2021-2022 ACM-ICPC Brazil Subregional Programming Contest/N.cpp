#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 233;

int c[maxn];
int lowbit(int x) {
    return x & (-x);
}
int n, q;

void add(int x, int d) {
    while(x <= n) {
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

int res[maxn];
vector<int> lst[maxn];
int value[maxn];
vector<tuple<int, int, int> > ask[maxn];

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    
    for (int i = 1; i <= n; i += 1) {
        cin >> value[i];
        lst[value[i]].emplace_back(i);
    }

    for (int i = 1; i <= q; i += 1) {
        int a, p, f;
        cin >> a >> p >> f;
        if(p <= value[a]) {
            continue;
        }
        ask[p].emplace_back(a + 1, a + f, i);
    }
    for (int i = 100000; i >= 0; i -= 1) {
        for (auto p : lst[i]) {
            add(p, 1);
        }
        for (auto [l, r, id] : ask[i]) {
            if(l <= r) res[id] = query(r) - query(l - 1);
        }
    }
    for (int i = 1; i <= q; i += 1) {
        cout << res[i] << "\n";
    }
    return 0;
}

/*
5 3
1 2 3 4 5
1 3 4
2 6 3
3 4 1
*/