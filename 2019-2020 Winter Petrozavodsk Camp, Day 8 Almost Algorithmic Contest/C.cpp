#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 233;

int mx[maxn << 2];
#define ls o << 1
#define rs o << 1 | 1

void up(int o) {
    mx[o] = max(mx[ls], mx[rs]);
}

void upd(int o, int tl, int tr, int l, int r, int v) {
    if(l > tr || tl > r) return;
    if(l <= tl && tr <= r) {
        mx[o] = v;
        return;
    }
    int mid = tl + tr >> 1;
    upd(ls, tl, mid, l, r, v);
    upd(rs, mid + 1, tr, l, r, v);
    up(o);
}

int query(int o, int tl, int tr, int l, int r) {
    if(l > tr || tl > r) return -1e9;
    if (l <= tl && tr <= r) return mx[o];
    int mid = tl + tr >> 1;
    return max(query(ls, tl, mid, l, r), query(rs, mid + 1, tr, l, r));
}

int n, a[maxn];
int go[maxn];
vector<int> del[maxn];
int dp[maxn];

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i += 1) {
        cin >> a[i];
    }
    stack<int> s;
    go[n + 1] = n + 1;
    for (int i = 0; i <= n; i += 1) {
        upd(1, 0, n, i, i, -1000000000);
        while(!s.empty() && a[i] > a[s.top()]) {
            go[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    while(!s.empty()) {
        go[s.top()] = n + 1;
        s.pop();
    }
    
    /*
    for (int i = 0; i <= n; i += 1) {
        cerr << go[i] <<  " \n"[i == n];
    }
    */
    
    dp[0] = 0;
    upd(1, 0, n, a[0], a[0], 0);
    int res = dp[0];
    del[go[go[0]] + 1].emplace_back(a[0]);
    for (int i = 1; i <= n; i += 1) {
        for (auto p : del[i]) {
            upd(1, 0, n, p, p, -1000000000);
        }
        dp[i] = query(1, 0, n, 0, a[i]) + 1;
       // cerr << dp[i] << " ";
        upd(1, 0, n, a[i], a[i], dp[i]);
        del[go[go[i]] + 1].emplace_back(a[i]);
        res = max(res, dp[i]);
    }
    cout << n - res << "\n";
    return 0;
}

/*
6
6 1 2 3 4 5

6
5 6 1 2 3 4

6
6 4 5 1 2 3
*/