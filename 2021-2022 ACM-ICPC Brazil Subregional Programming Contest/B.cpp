#include <bits/stdc++.h>
using namespace std;

#define sigma_size 26
const int maxn = 6e5 + 233;

int ch[maxn][sigma_size];
int f[maxn];
int sz;
int len[maxn];
int last;

void init(){
    last = sz = 1;
    f[1] = len[1] = 0;
    memset(ch[1], 0, sizeof(ch[1]));
}

void add(int c) {
    if(ch[last][c] && len[ch[last][c]] == len[last] + 1) {
        last = ch[last][c];
        return;
    }
    bool ok = 0;
    int x = ++sz;
    len[x] = len[last] + 1;
    int p;
    for (p = last; p && !ch[p][c]; p = f[p]) ch[p][c] = x;
    if(!p) f[x] = 1;
    else{
        int q = ch[p][c];
        if(len[x] == len[p] + 1) ok = 1;
        if(len[p] + 1 == len[q]) f[x] = q;
        else{
            int nq = ++sz;
            len[nq] = len[p] + 1;
            f[nq] = f[q];
            memcpy(ch[nq], ch[q], sizeof(ch[q]));
            for (; p && ch[p][c] == q; p = f[p]) ch[p][c] = nq;
            f[q] = f[x] = nq;
            if(ok) last = nq;
            else last = x;
            return;
        }
    }
    last = x;
}

int idx(char c) {
    return c - 'a';
}

int n, m;
string s;
int cnt[maxn];

void upd(int l, int r) {
    if(l > r) return;
    //cerr << "upd: " << l << " " << r << endl;
    cnt[l] += 1;
    cnt[r + 1] -= 1;
}

int main(){
    init();
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m >> s;
    for (int i = 0; i < m; i += 1) {
        string t;
        cin >> t;
        last = 1;
        for (int j = 0; j < t.size(); j += 1) {
            add(idx(t[j]));
        }
    }
    s = s + s;
    int u = 1;
    int cur_len = 0;
    vector<pair<int, int> > seg;
    for (int i = 0; i < 2 * n; i += 1) {
        int c = idx(s[i]);
        if(ch[u][c]) {
            u = ch[u][c];
            cur_len += 1;
        }
        else{
            while(u && !ch[u][c]) u = f[u];
            if(!u) u = 1, cur_len = 0;
            else cur_len = len[u] + 1, u = ch[u][c];
        }
        //cerr << i << " " << u << " " << cur_len << endl;
        seg.emplace_back(i - cur_len + 2, i + 1);
    }
    int lo = 1, hi = n, ans = 0;
    while(hi >= lo) {
        int mid = lo + hi >> 1;
        memset(cnt, 0, sizeof(cnt));
        for (auto [l, r] : seg) {
            if(r - l + 1 < mid) continue;
            upd(l + mid - 1, r);
            upd(r, r + n - mid);
        }
        bool flag = true;
        for (int i = 1; i < 2 * n; i += 1) {
            cnt[i] += cnt[i - 1];
            if(i >= n) {
                flag &= cnt[i] > 0;
            }
        }
        if(flag) {
            lo = mid + 1;
            ans = mid;
        }
        else hi = mid - 1;
    }
    cout << ans << "\n";
    return 0; 
}

/*
7 3
acmicpc
acm
icpc
maratona

11 4
competition
oncom
petition
ztxvu
fmwper

12 4
latinamerica
zyvu
okp
wsgh
kqpdb
*/