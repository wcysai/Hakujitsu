#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

int n, mod;
const int maxn = 2e6 + 233;
bool vis[maxn];
vector<int> prime;
int cnt[maxn];
int mn[maxn];
vector<int> factor[maxn];

void init(){
    for (int i = 2; i < maxn; i += 1) {
        if(!vis[i]) prime.emplace_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] < maxn; j += 1) {
            vis[i * prime[j]] = 1;
            if(i % prime[j] == 0) {
                break;
            }
        }
    }
    for (int i = 1; i < maxn; i += 1) {
        mn[i] = i;
    }
    for (int i = 2; i < maxn; i += 1) {
        if(vis[i]) continue;
        for (int j = i; j < maxn; j += i) {
            mn[j] = min(mn[j], i);
        }
    }
}

void solve(int cur, int c) {
    while(cur > 1) {
        cnt[mn[cur]] += c;
        cur /= mn[cur];
    }
}

void prepare(int n, int m) {
    memset(cnt, 0, sizeof(cnt));
    for (int i = n - m + 1; i <= n; i += 1) {
        solve(i, 1);
    }
    for (int i = 1; i <= m; i += 1) {
        solve(i, -1);
    }
}

int power(int q, int w) {
    int ret = 1;
    while(w) {
        if(w & 1) ret = 1ll * ret * q % mod;
        q = 1ll * q * q % mod;
        w >>= 1;
    }
    return ret;
}

int choose() {
    int ret = 1;
    for (int i = 2; i < maxn; i += 1) {
        ret = 1ll * ret * power(i, cnt[i]) % mod;
    }
    return ret;
}

using ll = long long;


int main(){
    init();
    cin >> n >> mod;
    if(n & 1) {
        cout << 0 << "\n";
        return 0;
    }
    prepare(n, n / 2);
    int c1 = choose();
    solve(n / 2 + 1, -1);
    int c0 = choose();
    c1 = 2ll * (c1 + mod - c0) % mod;
    int c2 = (1ll * power(2, n) + mod + mod - c0 - c1) % mod;
    cout << (c0 + 2ll * c1 + 3ll * c2) % mod << "\n";
    return 0;
}