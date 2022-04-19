#include <bits/stdc++.h>
using namespace std;

int T, n, a, b;

int main(){
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d %d", &n, &a, &b);
		if(n == 1) {
			puts("1");
			continue;
		}
		int lo = 0, hi = n - 1, ans = 0;
		while(hi >= lo) {
			int mid = (lo + hi) >> 1;
			if(1ll * mid * b <= 1ll * a * (n - 1)) {
				lo = mid + 1;
				ans = mid;
			}
			else hi = mid - 1;
		}
		cout << ans + 1 << '\n';
	}
	return 0;
}