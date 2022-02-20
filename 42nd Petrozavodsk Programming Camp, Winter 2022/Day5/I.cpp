#include <bits/stdc++.h>
#define F first
#define S second
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

const int maxn = 3e5 + 233;
int mn[maxn << 2];
int tag[maxn << 2];

#define ls o << 1
#define rs o << 1 | 1

void up(int o) {
    mn[o] = min(mn[ls], mn[rs]);
}

void down(int o) {
    if(tag[o]) {
        tag[ls] += tag[o];
        tag[rs] += tag[o];
        mn[ls] += tag[o];
        mn[rs] += tag[o];
        tag[o] = 0;
    }
}

void build(int o, int l, int r) {
    if(l == r) {
        mn[o] = -l;
        return;
    }
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    up(o);
}

void upd(int o, int tl, int tr, int l, int r, int v) {
    if(l > tr || tl > r) return;
    if(l <= tl && tr <= r) {
        tag[o] += v;
        mn[o] += v;
        return;
    }
    int mid = tl + tr >> 1;
    down(o);
    upd(ls, tl, mid, l, r, v);
    upd(rs, mid + 1, tr, l, r, v);
    up(o);
}

vector<pair<int, int> > add[maxn];
vector<pair<int, int> > del[maxn];
set<pair<int, int> > s;
int n, m;
vector<tuple<int, int, int> > lst[maxn];
int x[maxn], y[maxn], z[maxn];
int value[maxn];
int ord[maxn];

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    build(1, 1, n);
    for (int i = 1; i <= m; i += 1){
        cin >> z[i] >> x[i] >> y[i];
        add[x[i]].emplace_back(z[i], i);
        del[y[i] + 1].emplace_back(z[i], i);
    }
    s.emplace(1, 0);
    s.insert(make_pair(1, 0));
    for (int i = 1; i <= n; i += 1){
        for (auto x : add[i]) {
            s.emplace(x);
        }
        for (auto x : del[i]) {
            s.erase(s.find(x));
        }

        cerr << "list: " << endl;
        for (auto p : s) {
            cerr << p.F << " " << p.S << endl;
        }
        auto p1 = s.end(); p1--;
        auto p2 = p1;
        p2--;
        lst[p1->second].emplace_back(i, p1->first, p2->first);
        upd(1, 1, n, p1->first, n, 1);
        value[i] = p1->first;
        debug(i, p1->first, p2->first, p2->second, s.size());
    }
    for (int i = 1; i <= m; i += 1){
        for (auto [pos, pre, cur] : lst[i]) {
            value[pos] = cur;
            upd(1, 1, n, pre, n, -1);
            upd(1, 1, n, cur, n, 1);
        }
        if(mn[1] >= 0) {
            cout << "YES\n";
            for (int i = 1; i <= n; i += 1){
                ord[i] = i;
            }
            sort(ord + 1, ord + n + 1, [&](int x, int y) {
                return value[x] < value[y];
            });
            for (int i = 1; i <= n; i += 1){
                cout << ord[i] << " \n"[i == n];
            }
            return 0;
        }
        for (auto [pos, pre, cur] : lst[i]) {
            value[pos] = pre;
            upd(1, 1, n, pre, n, 1);
            upd(1, 1, n, cur, n, -1);
        }
    }
    cout << "NO\n";
    return 0;
}