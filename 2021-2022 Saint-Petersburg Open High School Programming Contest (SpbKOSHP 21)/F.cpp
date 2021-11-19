#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

const int maxn = 310;
using ll = long long;
int s[maxn], v[maxn], n;

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i += 1) {
        cin >> s[i] >> v[i];
    }
    vector<pair<int, int> > lst;
    int res = 0;
    if(n <= 2) res = n;
    for (int i = 1; i <= n; i += 1) {
        for (int j = i + 1; j <= n; j += 1) {
            lst.clear();
            for (int k = 1; k <= n; k += 1) {
                if(i == k || j == k) continue;
                int y = (k - i) * (s[j] - s[i]) - (j - i) * (s[k] - s[i]);
                int x = (j - i) * (v[k] - v[i]) - (k - i) * (v[j] - v[i]);
                if(x == 0 && y) {
                    continue;
                }
                if(x == 0 && y == 0) {
                    lst.emplace_back(x, y);
                    continue;
                }
                if(x < 0) x = -x, y = -y;
                if(y < 0) continue;
                int g = __gcd(x, y);
                x /= g;
                y /= g;
                lst.emplace_back(x, y);
            }
            sort(lst.begin(), lst.end());
            for (int p = 0; p < lst.size(); p += 1) {
                int q = p;
                while(q < lst.size() && lst[p] == lst[q]) {
                    q += 1;
                }
                res = max(res, q - p + 2);
                p = q - 1;
            }
        }
    }
    cout << res << "\n";
    return 0;
}

/*
3
0 1
0 3
3 2
*/