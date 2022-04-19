#include <bits/stdc++.h>
using namespace std;

int n, k;

int a[] = {4, 3, 4, 2, 3, 1, 4, 1, 5, 2, 3};

int main(){
	/*
	int n = 11;
	for (int i = 0; i < (1 << n); i += 1) {
		int c1 = 1, c2 = 1;
		vector<int> lst[2];
		for (int j = 0; j < n; j += 1) {
			lst[i >> j & 1].emplace_back(a[j]);
		}
		for (int j = 1; j < lst[0].size(); j += 1) {
			if(lst[0][j - 1] <= lst[0][j]) continue;
			c1 = 0;
		}
		for (int j = 1; j < lst[1].size(); j += 1) {
			if(lst[1][j - 1] >= lst[1][j]) continue;
			c2 = 0;
		}
		if(c1 && c2) {
			for (auto x : lst[0]) cout << x << ' ';
			cout << '\n';
			for (auto x : lst[1]) cout << x << ' ';
			cout << '\n';
		}
	}
	*/
	cin >> k;
	if(k == 0) {
		cout << 11 << '\n';
		for (int i = 0; i < 11; i += 1) {
			cout << a[i] << " \n"[i == 10];
		}
	}
	else if(k == 1) {
		cout << "6\n";
		cout << "1 1 4 5 1 4\n";
	}
	else {
		vector<int> ans;
		k-=1;
		int cur = 10000;
		for (int i=30;i>0;--i){
			int res=(1ll<<i)-1;
			while (k>=res){
				cur -= 1;
				k-=res;
 				for (int j=0;j<i;++j) ans.push_back(cur);
			}
		}
		if (k) ans.push_back(1);
		reverse(ans.begin(),ans.end());
		cout<<(int)ans.size()<<"\n";
		for(int i=0;i<(int)ans.size();i++) printf("%d%c",ans[i],i==(int)ans.size()-1?'\n':' ');
	}
	
	return 0;
}