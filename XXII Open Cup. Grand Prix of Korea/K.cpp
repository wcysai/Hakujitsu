#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

using pii = pair<double, int>;

tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update > tr;

const int maxn = 5e5 + 233;
int h[maxn][3];
int n, q;

const double gap = 1e13;
int lst[maxn];
int p[maxn];
int mn[maxn << 2];
int ord[maxn];
int dp[maxn];

void up(int o) {
    mn[o] = min(mn[o << 1], mn[o << 1 | 1]);
}

void upd(int o, int tl, int tr, int l, int r, int v) {
    if(l > tr || tl > r) return;
    if(l <= tl && tr <= r) {
        mn[o] = v;
        return;
    }
    int mid = tl + tr >> 1;
    upd(o << 1, tl, mid, l, r, v);
    upd(o << 1 | 1, mid + 1, tr, l, r, v);
    up(o);
}

int query(int o, int tl, int tr, int l, int r) {
    if(l > tr || tl > r) return 1e9;
    if(l <= tl && tr <= r) return mn[o];
    int mid = tl + tr >> 1;
    return min(query(o << 1, tl, mid, l, r), query(o << 1 | 1, mid + 1, tr, l, r));
}


int is_big(int x, int y){
    int res = 0;
    for (int i = 0; i < 3; i += 1) {
        res += h[x][i] < h[y][i];
    }
    return res >= 2;
}


void solve(int x, int y) {
    for (int i = 1; i <= n; i += 1) {
        ord[i] = i;
        upd(1, 1, n, i, i, 1e9);
    }
    sort(ord + 1, ord + n + 1, [&](int a, int b) {
        return h[a][x] > h[b][x];
    });
    for (int o = 1; o <= n; o += 1) {
        int i = ord[o];
        dp[i] = min(dp[i], query(1, 1, n, h[i][y], n));
        upd(1, 1, n, h[i][y], h[i][y], p[i]);
    }
}

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i += 1) {
        for (int j = 0; j < 3; j += 1) {
            cin >> h[i][j];
        }
    }
    tr.insert(pii(0, 1));
    if(is_big(1, 2)) {
        tr.insert(pii(gap, 2));
    }
    else{
        tr.insert(pii(-gap, 2));
    }
    
    for (int i = 3; i <= n; i += 1) {
        auto [value, id] = *tr.find_by_order(0);
        if(is_big(i, id)) {
            tr.insert(pii(value - gap, i));
            continue;
        } 
        tie(value, id) = *tr.rbegin();
        if(is_big(id, i)) {
            tr.insert(pii(value + gap, i));
            continue;
        }
        int lo = 0, hi = int(tr.size()) - 2;
        double cur_value = 0;
        while(lo <= hi) {
            int mid = (lo + hi) / 2;
            auto [v1, id1] = *tr.find_by_order(mid);
            auto [v2, id2] = *tr.find_by_order(mid + 1);
            if(is_big(id1, i) && is_big(i, id2)) {
                cur_value = (v1 + v2) / 2;
                break;
            }
            if(is_big(i, id1)) {
                hi = mid - 1;
            }
            else if(is_big(id2, i)){
                lo = mid + 1;
            }
            else assert(0);
        }
        tr.insert(pii(cur_value, i));
    }
    for (int i = 1; i <= n; i += 1) {
        lst[i] = tr.find_by_order(i - 1)->second;
        p[lst[i]] = i;
    }
    for (int i = 1; i <= n; i += 1) {
        dp[i] = p[i];
        //cerr << lst[i] << " \n"[i == n];
    }
    solve(0, 1);
    solve(0, 2);
    solve(1, 2);
    for (int i = n - 1; i; i -= 1) {
        dp[lst[i]] = min(dp[lst[i]], dp[lst[i + 1]]);
    }

    /*
    for (int i = 1; i <= n; i += 1) {
        cerr << dp[i] << " \n"[i == n];
    }
    */
    cin >> q;
    while(q--) {
        int x, y;
        cin >> x >> y;
        cout << (dp[x] <= p[y] ? "YES" : "NO") << "\n";
    }

    return 0;
}

/*
4
2 4 3
3 1 4
4 3 2
1 2 1

3
1 2
2 1
3 4

4
1 1 1
2 2 2
3 3 3
4 4 4
5
1 2
1 3
1 4
2 1
3 1
*/