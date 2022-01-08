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
 
const int maxn = 1e6 + 233;
 
string s[maxn];
int n, q;
string t;
 
using pii = pair<int, int>;
vector<pii> h[maxn];
vector<int> go[maxn];
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;
 
int power(int q, int w, int mod) {
    int ret = 1;
    while(w) {
        if(w & 1) ret = 1ll * ret * q % mod;
        q = 1ll * q * q % mod;
        w >>= 1;
    }
    return ret;
}
 
pii bin[maxn], inv[maxn];
 
pii operator+(pii a, pii b) {
    return {(a.first + b.first) % mod1, (a.second + b.second) % mod2};
}
 
pii operator-(pii a, pii b) {
    return {(a.first + mod1 - b.first) % mod1, (a.second + mod2 - b.second) % mod2};
}
 
pii operator*(pii a, pii b) {
    return {(1ll * a.first * b.first) % mod1, (1ll * a.second * b.second) % mod2};
}
 
vector<pii> get_hash(string x) {
    vector<pii> h(x.size() + 5);
    for (int i = 0; i < x.size(); i += 1) {
        h[i + 1] = h[i] * bin[1] + pii(x[i], x[i]);
    }
    return h;
}
 
struct info{
    int L, R, l, r;
    char c;
};
 
int cmp(int i, int pos, int len, char c) {
 
    if(len == 0) return 0;
    if(s[i][pos - 1] != c) {
        if(s[i][pos - 1] < c) return -1;
        if(s[i][pos - 1] == c) return 0;
        if(s[i][pos - 1] > c) return 1;
    }
    
    int nxt = min(go[i][pos] - pos, len);
    if(nxt == len) return 0;
    else if(nxt + pos - 1 == s[i].size()) return -1;
    if(s[i][nxt + pos - 1] < c) return -1;
    if(s[i][nxt + pos - 1] == c) return 0;
    if(s[i][nxt + pos - 1] > c) return 1;
}
 
pii solve(int l, int r, int pos, int len, char c) {
    int lo = l + 1, hi = r - 1, nl = l;
    while(hi >= lo) {
        int mid = lo + hi >> 1;
        if(cmp(mid, pos, len, c) == -1) {
            nl = mid;
            lo = mid + 1;
        }
        else hi = mid - 1;
    }
    lo = l + 1, hi = r - 1;
    int nr = r;
    while(hi >= lo) {
        int mid = lo + hi >> 1;
        if(cmp(mid, pos, len, c) == 1) {
            nr = mid;
            hi = mid - 1;
        }
        else lo = mid + 1;
    }
    return {nl, nr};
}
 
int main(){
    bin[0] = inv[0] = {1, 1};
    bin[1] = {19260817, 19990303};
    inv[1] = {power(19260817, mod1 - 2, mod1), power(19990303, mod2 - 2, mod2)};
    for (int i = 2; i < maxn; i += 1) {
        bin[i] = bin[i - 1] * bin[1];
        inv[i] = inv[i - 1] * inv[1];
    }
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    vector<info> lst;
    string t;
    cin >> t;
    for (int i = 1; i <= n; i += 1){
        cin >> s[i];
    }
    sort(s + 1, s + n + 1, [&](string a, string b) {
        for (int i = 0; i < min(a.size(), b.size()); i += 1) {
            if(a[i] < b[i]) return true;
            if(a[i] > b[i]) return false;
        }
        if(a.size() < b.size()) return true;
        return false;
    });
 
    
    for (int i = 1; i <= n; i += 1) {
        h[i] = get_hash(s[i]);
        go[i].resize(s[i].size() + 5);
        go[i][s[i].size()] = s[i].size() + 1;
        go[i][s[i].size() + 1] = s[i].size() + 1;
        for (int j = int(s[i].size()) - 2; j >= 0; j -= 1) {
            go[i][j + 1] = s[i][j] == s[i][j + 1] ? go[i][j + 2] : j + 2;
        }
    }
 
    
    lst.emplace_back(info{0, 0, 0, n + 1, 'a'});
    for (int i = 0; t[i]; i += 1) {
        auto [nl, nr] = solve(lst.back().l, lst.back().r, lst.back().R + 1, 1, t[i]);
        lst.emplace_back(info{lst.back().R + 1, lst.back().R + 1, nl, nr, t[i]});
    }
    cout  << lst.back().l << "\n";
 
    /*
    for (auto [L, R, l, r, c] : lst) {
        debug(L, R, l, r, c);
    }
    */
    while(q--) {
        string c;
        int cur;
        cin >> cur >> c;
        while(!lst.empty() && lst.back().L >= cur) {
            lst.pop_back();
        }
        
        if(!lst.empty() && lst.back().R >= cur) {
            auto cc = lst.back().c;
            lst.pop_back();
            if(cur - lst.back().R - 1 > 0){
                auto [nl, nr] = solve(lst.back().l, lst.back().r, lst.back().R + 1, cur - lst.back().R - 1, cc);
                lst.emplace_back(info{lst.back().R + 1, cur - 1, nl, nr, cc});
            }
        }
 
        auto [nl, nr] = solve(lst.back().l, lst.back().r, lst.back().R + 1, t.size() - cur + 1, c[0]);
        lst.emplace_back(info{cur, t.size(), nl, nr, c[0]});
        
        /*
        cerr << "after: " << q << endl;
        for (auto [L, R, l, r, c] : lst) {
            debug(L, R, l, r, c);
        }
        */
        cout << lst.back().l << "\n";
    }
    return 0;
}
 
/*
4 3
anatoly
boris
anatooo
anbbbbu
anba
5 o
3 b
7 x
 
5 0
buuuu
buz
ababa
build
a
aba
 
5 5
abcde
buz
ababa
build
a
aba
1 b
3 z
2 u
4 z
1 a
 
5 3
aaa
a
aa
ab
aba
abc
2 b
3 c
3 d
*/