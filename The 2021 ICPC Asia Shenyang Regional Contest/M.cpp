#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e6 + 233;
int s[maxn], sa[maxn], t[maxn], t2[maxn], c[maxn], n, r[maxn], h[maxn];
char str[maxn];

void build_sa(int n, int m) {
    int i, *x = t, *y = t2;
    for (int i = 0; i < m; i += 1) c[i] = 0;
    for (int i = 0; i < n; i += 1) c[x[i] = s[i]] += 1;
    for (int i = 1; i < m; i += 1) c[i] += c[i - 1];
    for (int i = n - 1; i >= 0; i -= 1) sa[--c[x[i]]] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int p = 0;
        for (int i = n - k; i < n; i += 1) y[p++] = i;
        for (int i = 0; i < n; i += 1) if(sa[i] >= k) y[p++] = sa[i] - k;
        for (int i = 0; i < m; i += 1) c[i] = 0;
        for (int i = 0; i < n; i += 1) c[x[y[i]]] += 1;
        for (int i = 0; i < m; i += 1) c[i] += c[i - 1];
        for (int i = n - 1; i >= 0; i -= 1) sa[--c[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1;
        x[sa[0]] = 0;
        for (int i = 1; i < n; i += 1)
            x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
        if(p >= n) break;
        m = p;
    }
}

void getheight(){
    int i, j, k = 0;
    for (i = 1; i <= n; i += 1) r[sa[i]] = i;
    for (i = 0; i < n; h[r[i++]] = k)
        for(k ? k-- : 0, j = sa[r[i] - 1]; s[i + k] == s[j + k]; k++);
}

int mn[1100005][25];
int lg[maxn];

void rmq_init(){
    for (int i = 2; i < maxn; i += 1) {
        lg[i] = lg[i >> 1] + 1;
    }
    for (int i = 1; i <= n; i += 1) {
        mn[i][0] = h[i];
    }
    for (int j = 1; (1 << j) <= n; j += 1) {
        for (int i = 1; i + (1 << j) - 1 <= n; i += 1) {
            mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int qmin(int l, int r) {
    if(l > r) swap(l, r);
    int k = lg[r - l + 1];
    return min(mn[l][k], mn[r - (1 << k) + 1][k]);
}

int lcp(int l, int r) {
    if(l == r) return n - sa[l];
    if(l > r) swap(l, r);
    return qmin(l + 1, r);
}

int res[maxn];

int main(){
    scanf("%s", str);
    n = strlen(str);
    for (int i = 0; i < n; i += 1) {
        s[i] = str[i] - 'a' + 1;
        s[i] = 50 - s[i];
    }
   
    s[n] = 100; 
    build_sa(n + 2, 200);
    getheight();
    rmq_init();

    /*
    for (int i = 1; i <= n; i += 1) {
        cerr << sa[i] << " \n"[i == n];
    }
    for (int i = 1; i <= n; i += 1) {
        cerr << h[i] << " \n"[i == n];
    }
    cout << lcp(1, 2) << "\n";
    */
    vector<int> sta;
    for (int i = n; i; i -= 1) {
        while(!sta.empty() && sa[i] < sa[sta.back()]) {
            sta.pop_back();
        }
        sta.push_back(i);
    }

    /*

    for (auto x : sta) {
        cerr << sa[x] << " ";
    }

    cerr << "\n\n\n";
    */


    vector<pair<int, int> > lst;
    
    lst.emplace_back(r[0], 0);
    for (int i = 1; i < sta.size(); i += 1) {
        while(!lst.empty()) {
            auto [x, y] = lst.back();
            int lc = lcp(sta[i], x);
            if(sa[sta[i]] + lc <= y) {
                lst.pop_back();
            }
            else{
                lst.emplace_back(sta[i], sa[sta[i]] + lc);
                break;
            }
        }
        if(lst.empty()) {
            lst.emplace_back(sta[i], sa[sta[i]]);
        }
    }
    
    /*
    for (auto [x, y] : lst) {
        cerr << x << " " << y << endl;
    }
    */
    for (int i = 0; i + 1 < lst.size(); i += 1) {
        auto [x, y] = lst[i];
        for (int j = y; j < lst[i + 1].second; j += 1) {
            res[j] = sa[lst[i].first] + 1;
        }
    }
    for (int i = lst.back().second; i < n; i += 1) {
        res[i] = sa[lst.back().first] + 1;
    }
    for (int i = 0; i < n; i += 1) {
        printf("%d %d\n", res[i], i + 1);
    }
    return 0;
}

/*
aaaaa
aaaa
*/