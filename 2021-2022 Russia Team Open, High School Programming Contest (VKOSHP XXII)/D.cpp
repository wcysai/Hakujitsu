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

int n;
using ll = long long;
vector<int> a, b;

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    a.push_back(0);
    b.push_back(0);
    for (int i = 1; i <= n; i += 1){
        int x;
        cin >> x;
        a.push_back(x);
    }
    for (int i = 1; i <= n; i += 1){
        int x;
        cin >> x;
        b.push_back(x);
    }
    if(accumulate(a.begin(), a.end(), 0ll) > accumulate(b.begin(), b.end(), 0ll)) {
        cout << "-1\n";
        return 0;
    }
    auto check = [&](int mid) {
        auto ta = a;
        auto tb = b;
        int head = 1, tail = mid + 1;
        for (int i = 1; i <= n; i += 1) {
            while(i - head > mid) head += 1;
            while(head < n && ta[i] > tb[head]) {
                ta[i] -= tb[head];
                head += 1;
            }
            if(tb[head] < ta[i]) return false;
            tb[head] -= ta[i];
            if(head > tail) return false;
            if(tail < n) tail += 1;
        }
        return true;
    };
    int lo = 0, hi = n - 1, ans = n;
    while(hi >= lo) {
        int mid = lo + hi >> 1;
        if(check(mid)) {
            hi = mid - 1;
            ans = mid;
        }
        else lo = mid + 1;
    }
    cout << ans << "\n";
    return 0;
}

/*
4
6 14 70 1
70 3 16 5

1
2
2

1
3
2
*/