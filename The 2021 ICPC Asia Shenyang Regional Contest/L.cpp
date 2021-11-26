#include<bits/stdc++.h>
using namespace std;

const int mod = 998244353;

void add(int &x, int y) {
    x += y;
    if(x >= mod) x -= mod;
}

void sub(int &x, int y) {
    x -= y;
    if(x < 0) x += mod;
}

const int maxn = 4040;
vector<int> G[maxn];
int dp[maxn][maxn][2];
int sz[maxn];
int tmp[maxn][2];

void dfs(int u, int fa) {
    sz[u] = 1;
    dp[u][0][0] = 1; 
    for (auto v : G[u]) {
        if(v == fa) continue;
        dfs(v, u);
        memset(tmp, 0, sizeof(tmp));
        for (int i = sz[u]; i >= 0; i -= 1) {
            for (int j = sz[v]; j >= 0; j -= 1) {
                add(tmp[i + j][0], 1ll * dp[u][i][0] * (dp[v][j][0] + dp[v][j][1]) % mod);
                add(tmp[i + j][1], 1ll * dp[u][i][1] * (dp[v][j][0] + dp[v][j][1]) % mod);
                add(tmp[i + j + 1][1], 1ll * dp[u][i][0] * dp[v][j][0] % mod);
            }
        }
        memcpy(dp[u], tmp, sizeof(tmp));
        sz[u] += sz[v];
    }
}

int n;
int f[maxn];
int fac[maxn];
int choose[maxn][maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    fac[0] = 1;
    choose[0][0] = 1;
    for (int i = 1; i <= 2 * n; i += 1) {
        choose[i][0] = 1;
        for (int j = 1; j <= i; j += 1) {
            add(choose[i][j], choose[i - 1][j]);
            add(choose[i][j], choose[i - 1][j - 1]);
        }
    }
    for (int i = 1; i <= 2 * n; i += 1) {
        fac[i] = 1ll * fac[i - 1] * (2 * i - 1) % mod;
    }
    for (int i = 1; i < 2 * n; i += 1) {
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    dfs(1, 0);
    for (int i = 0; i <= n; i += 1) {

        f[i] = 1ll * (dp[1][i][0] + dp[1][i][1]) * fac[n - i] % mod;
        //cerr << (dp[1][i][0] + dp[1][i][1]) % mod << " " << n - i << " \n";
    }
    for (int i = n; i >= 0; i -= 1) {
        for (int j = i + 1; j <= n; j += 1) {
            sub(f[i], 1ll * f[j] * choose[j][i] % mod);
        }
    }
    cout << f[0] << "\n";
    return 0;
}

/*
2
1 2
1 3
3 4

3
1 2
2 3
3 4
4 5
5 6
*/