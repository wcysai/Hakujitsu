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

const int maxn = 2020;
int dp[maxn][maxn][3][3];
int n, m, T;
char s[maxn][maxn];
tuple<int, int, int, int> pre[maxn][maxn][3][3];

int a[maxn][maxn];

int ch[maxn], cl[maxn];

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i <= n + 5; i += 1) {
            ch[i] = 0;
        }
        for (int i = 0; i <= m + 5; i += 1) {
            cl[i] = 0;
        }
        for (int i = 1; i <= n; i += 1) {
            scanf("%s", s[i] + 1);
            for (int j = 1; j <= m; j += 1) {
                if(s[i][j] == '.') a[i][j] = 0;
                if(s[i][j] == '#') a[i][j] = -1;
                if(s[i][j] == 'O') a[i][j] = 1;
                if(s[i][j] == '@') a[i][j] = 2;
            }
        }
        for (int i = 0; i <= n + 5; i += 1) {
            for (int j = 0; j <= m + 5; j += 1) {
                memset(dp[i][j], 0, sizeof(dp[i][j]));
            }
        }
        if(a[1][1] == -1) {
            puts("NIE");
            continue;
        }
        if(a[1][1] == 0) {
            dp[1][1][0][0] = 1;
        }
        if(a[1][1] == 1) {
            dp[1][1][1][1] = 1;
            dp[1][1][2][2] = 1;
        }
        if(a[1][1] == 2) {
            dp[1][1][1][2] = 1;
            dp[1][1][2][1] = 1;
        }

        auto upd = [&](int i, int j, int k1, int k2, int ni, int nj) {
            if(a[ni][nj] == -1) return;
            if(a[ni][nj] == 0) {
                dp[ni][nj][k1][k2] = 1;
                pre[ni][nj][k1][k2] = {i, j, k1, k2}; 
            }
            if(a[ni][nj] == 1) {
                if(ni == i + 1) {
                    if(k2) {
                        dp[ni][nj][k2][k2] = 1;
                        pre[ni][nj][k2][k2] = {i, j, k1, k2};
                    }
                    else{
                        dp[ni][nj][1][1] = 1;
                        pre[ni][nj][1][1] = {i, j, k1, k2};
                        dp[ni][nj][2][2] = 1;
                        pre[ni][nj][2][2] = {i, j, k1, k2};
                    }
                }
                else{
                    if(k1) {
                        dp[ni][nj][k1][k1] = 1;
                        pre[ni][nj][k1][k1] = {i, j, k1, k2};
                    }
                    else{
                        dp[ni][nj][1][1] = 1;
                        pre[ni][nj][1][1] = {i, j, k1, k2};
                        dp[ni][nj][2][2] = 1;
                        pre[ni][nj][2][2] = {i, j, k1, k2};
                    } 
                }
            }
            if(a[ni][nj] == 2) {
                if(ni == i + 1) {
                    if(k2) {
                        dp[ni][nj][((k2 - 1) ^ 1) + 1][k2] = 1;
                        pre[ni][nj][((k2 - 1) ^ 1) + 1][k2] = {i, j, k1, k2};
                    }
                    else{
                        dp[ni][nj][1][2] = 1;
                        pre[ni][nj][1][2] = {i, j, k1, k2};
                        dp[ni][nj][2][1] = 1;
                        pre[ni][nj][2][1] = {i, j, k1, k2};
                    }
                }
                else{
                    if(k1) {
                        dp[ni][nj][k1][((k1 - 1) ^ 1) + 1] = 1;
                        pre[ni][nj][k1][((k1 - 1) ^ 1) + 1] = {i, j, k1, k2};
                    }
                    else{
                        dp[ni][nj][1][2] = 1;
                        pre[ni][nj][1][2] = {i, j, k1, k2};
                        dp[ni][nj][2][1] = 1;
                        pre[ni][nj][2][1] = {i, j, k1, k2};
                    } 
                } 
            }
        };

        for (int i = 1; i <= n; i += 1) {
            for (int j = 1; j <= m; j += 1) {
                for (int k1 = 0; k1 < 3; k1 += 1) {
                    for (int k2 = 0; k2 < 3; k2 += 1) {
                        if(!dp[i][j][k1][k2]) continue;
                        if(i + 1 <= n){
                            upd(i, j, k1, k2, i + 1, j);
                        }
                        if(j + 1 <= m) {
                            upd(i, j, k1, k2, i, j + 1);
                        }
                    }
                }
            }
        }

        int cn = n, cm = m, k1 = -1, k2 = -1;
        for (int i = 0; i < 3; i += 1) {
            for (int j = 0; j < 3; j += 1) {
                if(dp[n][m][i][j]) {
                    k1 = i;
                    k2 = j;
                }
            }
        }
        if(k1 == -1) {
            puts("NIE");
            continue;
        }
        else puts("TAK");
        string path;
        while(1) {
            auto [pn, pm, pk1, pk2] = pre[cn][cm][k1][k2];
            if(k1) ch[cn] = k1 - 1;
            if(k2) cl[cm] = k2 - 1;
            if(cn == 1 && cm == 1) break;
            if(pn != cn) path += "D";
            else path += "P";
            //debug(cn, cm, k1, k2, pn, pm, pk1, pk2);
            tie(cn, cm, k1, k2) = pre[cn][cm][k1][k2];
            
        }
        for (int i = 1; i <= n; i += 1) {
            putchar(ch[i] ? 'T' : 'N');
        }
        puts("");
        for (int i = 1; i <= m; i += 1) {
            putchar(cl[i] ? 'T' : 'N');
        }
        puts("");
        reverse(path.begin(), path.end());
        for (int i = 0; path[i]; i += 1) {
            putchar(path[i]);
        }
        puts("");
    }
    return 0;
}

/*
2
4 5
..#..
@@O@@
##@#O
..@.@
2 2
@O
@O
*/