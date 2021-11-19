#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 233;
int mn[maxn << 2];
int value[maxn];

#define ls o << 1
#define rs o << 1 | 1

void up(int o) {
    mn[o] = min(mn[ls], mn[rs]);
}

void build(int o, int l, int r) {
    if(l == r) {
        mn[o] = value[l];
        return;
    }
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    up(o);
    //cerr << l << " " << r << " " << mn[o] << endl;
}

int query(int o, int tl, int tr, int l, int r) {
    if(l > tr || tl > r) return 1e9;
    if(l <= tl && tr <= r) return mn[o];
    int mid = tl + tr >> 1;
    return min(query(ls, tl, mid, l, r), query(rs, mid + 1, tr, l, r));
}

int n, m;

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    build(1, 1, n);
    int pre_len = n;
    for (int i = 1; i <= m; i += 1) {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;
        for (int j = 1; j <= r - l; j += 1) {
            value[j] = 1e9;
        }
        for (int j = r - l + 1; j <= n; j += 1) { 
            value[j] = query(1, 1, n, j - len + 1, min(n, j + pre_len - 1)) + abs(j - r);
        }

        /*
        for (int j = 1; j <= n; j += 1) {
            cerr << value[j] << " \n"[j == n];
        }
        
        cerr << "\n\n";
        */
        
        build(1, 1, n);
        /*
        if(i == 1) {
            cerr << "test: " << query(1, 1, n, 4, n) << "\n";
        }
        */
        pre_len = len;
    }
    cout << query(1, 1, n, 1, n) << "\n";
    return 0;
}

/*
9 3
1 2
4 5
7 9
*/