#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

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

const int mod = 1e9 + 7;
void add(int &x, int y) {
    x += y;
    if(x >= mod) x -= mod;
}

void sub(int &x, int y) {
    x -= y;
    if(x < 0) x += mod;
}

gp_hash_table<int, int> cnt, sum;

const int maxn = 1e6 + 233;
int a[maxn], b[maxn], can[maxn];
const int inf = 1e9;
int dp[maxn];
int n, k;
int res;

void solve(int l, int r) {
    if(l > r) return;
    int mid = l + r >> 1;
    // mnl < mnr
    int mnl = inf, mnr = inf;
    int j = mid;
    int pre_mod = 0;
    int pre_sum = 0;
    int suf_sum = 0;
    int suf_mod = 0;
    int all = 0;
    for (int i = mid; i >= l; i -= 1) {
        if(can[i]) mnl = min(mnl, dp[i]);
        add(suf_sum, a[i]);
        suf_mod = (suf_mod + a[i]) % k;
        while(j <= r && (!can[j] || dp[j] > mnl)) {
            pre_mod = (pre_mod + a[j]) % k;
            add(pre_sum, a[j]);
            add(all, pre_sum);
            cnt[pre_mod] += 1;
            add(sum[pre_mod], pre_sum);
            j += 1;
        }
        add(res, all);
        add(res, 1ll * (j - mid) * suf_sum % mod);
        sub(res, 1ll * a[mid] * (j - mid) % mod);
        int rem = (k - suf_mod + a[mid]) % k;
        if(mnl == inf) {
            sub(res, (1ll * (suf_sum + mod - a[mid]) * cnt[rem] + sum[rem]) % mod);
        }
        else{
            sub(res, 1ll * cnt[rem] * mnl % mod);
        }
    }
    cnt.clear();
    sum.clear();

    mnl = inf, mnr = inf;
    j = mid;
    pre_mod = 0;
    pre_sum = 0;
    suf_sum = 0;
    suf_mod = 0;
    all = 0;
   // debug(l, r, res); 
    // mnr <= mnl
    for (int i = mid; i <= r; i += 1) {
        if(can[i]) mnr = min(mnr, dp[i]);
        add(suf_sum, a[i]);
        suf_mod = (suf_mod + a[i]) % k;
        while(j >= l && (!can[j] || dp[j] >= mnr)) {
            pre_mod = (pre_mod + a[j]) % k;
            add(pre_sum, a[j]);
            add(all, pre_sum);
            cnt[pre_mod] += 1;
            add(sum[pre_mod], pre_sum);
            j -= 1;
        }
        
        add(res, all);
        add(res, 1ll * (mid - j) * suf_sum % mod);
        sub(res, 1ll * (mid - j) * a[mid] % mod);
        int rem = (k - suf_mod + a[mid]) % k;
        if(mnr == inf) {
            sub(res, (1ll * (suf_sum + mod - a[mid]) * cnt[rem] + sum[rem]) % mod);
        }
        else{
            sub(res, 1ll * cnt[rem] * mnr % mod);
        }
       // debug(l, r, i, mnr, j, rem, suf_mod, a[mid], res);
    }
   // debug(l, r, res); 
    cnt.clear();
    sum.clear();
    solve(l, mid - 1);
    solve(mid + 1, r);
}
int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i += 1){
        cin >> a[i] >> b[i];
        if(a[i] < b[i]) swap(a[i], b[i]);
        dp[i] = a[i] - b[i];
        can[i] = (a[i] % k) != (b[i] % k);
        if(!can[i]) dp[i] = inf;
        can[i] = 1;
    }
    res = 0;
    solve(1, n);
    cout << res << "\n";
    return 0;
}

/*
3 3
1 2
2 3
3 1

5 5
4 1
4 2
2 3
2 4
1 5
*/