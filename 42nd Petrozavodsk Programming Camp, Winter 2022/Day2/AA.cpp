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

const int maxn = 5e5 + 233;
#define ls o << 1
#define rs o << 1 | 1

using pii = pair<int*, int>;

struct Tree1{
    int mn[maxn << 2];

    void up(int o, vector<pii> &backup) {
        backup.emplace_back(&mn[o], mn[o]);
        mn[o] = min(mn[ls], mn[rs]);
    }

    void build(int o, int l, int r) {
        mn[o] = 1e8;
        if(l == r) {
            return;
        }
        int mid = l + r >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
    }

    void upd(int o, int tl, int tr, int l, int r, int v, vector<pii> &backup) {
        if(l > tr || tl > r) return;
        if(l <= tl && tr <= r) {
            backup.emplace_back(&mn[o], mn[o]);
            mn[o] = min(mn[o], v);
            return;
        }   
        int mid = tl + tr >> 1;
        upd(ls, tl, mid, l, r, v, backup);
        upd(rs, mid + 1, tr, l, r, v, backup);
        up(o, backup);
    }

    int query(int o, int tl, int tr, int l, int r) {
        if(l > tr || tl > r || l > r) return 1e8;
        if(l <= tl && tr <= r) return mn[o];
        int mid = tl + tr >> 1;
        return min(query(ls, tl, mid, l, r), query(rs, mid + 1, tr, l, r));
    }
}T[2];

multiset<int> s;
int res[maxn];

void undo(vector<pii> &backup) {
    while(!backup.empty()) {
        *backup.back().first = backup.back().second;
        backup.pop_back();
    }
}

struct Tree2{
    vector<tuple<int, int, int> > event[maxn << 2];

    void upd(int o, int tl, int tr, int l, int r, tuple<int, int, int> v) {
        if(l > tr || tl > r) return;
        if(l <= tl && tr <= r) {
            event[o].emplace_back(v);
            return;
        }
        int mid = tl + tr >> 1;
        upd(ls, tl, mid, l, r, v);
        upd(rs, mid + 1, tr, l, r, v);
    } 

    void getans(int o, int tl, int tr) {
        vector<pii> b[2];
        multiset<int> tmp;
        for (auto [op, x, y] : event[o]) {
            int lo = 0, hi = 500000, ans = 100000000;
            while(hi >= lo) {
                int mid = lo + hi >> 1;
                if(T[op ^ 1].query(1, 0, 250000, 0, mid - x) + y <= mid) {
                    hi = mid - 1;
                    ans = mid;
                }
                else lo = mid + 1;
            }
            printf("x=%d y=%d ans=%d\n",x,y,ans);
            tmp.emplace(ans);
            s.emplace(ans);
            //debug(op, x, y);
            T[op].upd(1, 0, 250000, x, x, y, b[op]);
            //debug(op, x, y);
        }
        if(tl == tr) {
            res[tl] = *s.begin();
            undo(b[0]);
            undo(b[1]);
            for (auto x : tmp) {
                s.erase(s.find(x));
            }
            return;
        }
        int mid = tl + tr >> 1;
        getans(ls, tl, mid);
        getans(rs, mid + 1, tr);
        undo(b[0]);
        undo(b[1]);
        for (auto x : tmp) {
            s.erase(s.find(x));
        } 
    }
}S;

int op[maxn], x[maxn], y[maxn], z[maxn];
map<pair<int, int>, int> cnt[2], timeline[2];
int n;

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    s.insert(100000000);
    cin >> n;
    T[0].build(1, 0, 250000);
    T[1].build(1, 0, 250000);
    for (int i = 1; i <= n; i += 1){
        cin >> op[i] >> z[i] >> x[i] >> y[i];
        z[i] -= 1;
        if(op[i] == 1) {
            if(cnt[z[i]][make_pair(x[i], y[i])]++ == 0) {
                timeline[z[i]][make_pair(x[i], y[i])] = i;
            }
        }
        else{
            if(--cnt[z[i]][make_pair(x[i], y[i])] == 0){
                S.upd(1, 1, n, timeline[z[i]][make_pair(x[i], y[i])], i - 1, make_tuple(z[i], x[i], y[i]));
               // debug(z[i], x[i], y[i], timeline[z[i]][make_pair(x[i], y[i])], i - 1);
                timeline[z[i]].erase(timeline[z[i]].find(make_pair(x[i], y[i])));
                
            }
        }
    }
    for (int i = 0; i < 2; i += 1) {
        for (auto [it, t] : timeline[i]) {
            S.upd(1, 1, n, t, n, make_tuple(i, it.first, it.second));
           // debug(i, it.first, it.second, t, n);
        }
    }
    S.getans(1, 1, n);
    for (int i = 1; i <= n; i += 1){
        if(res[i] >= 1e7) res[i] = -1;
        cout << res[i] << "\n";
    }
    return 0;
}