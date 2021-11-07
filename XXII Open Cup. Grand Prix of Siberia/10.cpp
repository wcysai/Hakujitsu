#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
#define N 2049
#define mod 998244353
#define G 3
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const double pi = acos(-1.0);
int qpow(int x, int y) {
	int ret = 1;
	for(; y; y >>= 1, x = 1LL*x * x % mod) if(y & 1) ret = 1LL*ret * x % mod; 
	return ret;
}
int rev[N];
void ntt(int *a, int n, int o) {  //NTT
	int G_inv = qpow(G, mod - 2), n_inv = qpow(n, mod - 2);
	for(int i = 0; i < n; i ++) if(i > rev[i]) swap(a[i], a[rev[i]]);
	for(int len = 2; len <= n; len <<= 1) {
		int w0 = qpow((o == 1)? G : G_inv, (mod - 1) / len);
		for(int j = 0; j < n; j += len) {
			int wn = 1;
			for(int p = j; p < j + (len >> 1); p ++, wn = 1LL* wn * w0 % mod) {
				int X = a[p], Y = 1LL* wn * a[p + (len >> 1)]  % mod;
				a[p] = (X + Y) % mod;
				a[p + (len >> 1)] = (X - Y + mod) % mod;
			}
		}
	}
	if(o == -1) 
		for(int i = 0; i < n; i ++) a[i] = 1LL* a[i] * n_inv % mod;
}
int n,m,x,y, a[N][N], b[N][N], al[N][N], bl[N][N];
string s[N],t[N];
int main() 
{
    scanf("%d%d%d%d",&n,&m,&x,&y);
    for(int i=0;i<n;i++) cin>>s[i];
    for(int i=0;i<)
	scanf("%d", &n);
	for(int i = 0; i <= n; i ++) 
		for(int j = 0; j <= n; j ++) scanf("%lld", &a[i][j]);
	for(int i = 0; i <= n; i ++) 
		for(int j = 0; j <= n; j ++) scanf("%lld", &b[i][j]);
		
	int len = 1;
	for(;len <= n + n; len <<= 1);
	
	for(int i = 1; i < len; i ++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (len >> 1));
	
	for(int i = 0; i <= n; i ++) ntt(a[i], len, 1), ntt(b[i], len, 1); //先搞列
	
	m = n;
	n = len;
	for(int i = 0; i <= n; i ++)
		for(int j = 0; j <= n; j ++) al[j][i] = a[i][j], bl[j][i] = b[i][j];//把矩阵转置一下
	
	for(int i = 0; i <= n; i ++) ntt(al[i], len, 1), ntt(bl[i], len, 1);//在搞行
	
	for(int i = 0; i <= n; i ++) {
		for(int j = 0; j <= n; j ++) {
			al[i][j] = al[i][j] * bl[i][j] % mod;//乘起来
		}
		ntt(al[i], len, -1);//先按照列IDFT回去
		for(int j = 0; j <= n; j ++)
			a[j][i] = al[i][j];//转置
	}
	
	for(int i = 0; i < n; i ++) ntt(a[i], len, -1);//再按照行IDFT回去

	for(int i = 0; i < 2 * m + 1; i ++) {//按题目要求输出即可
		int ans = 0;
		for(int j = 0; j < n; j ++) ans = ans ^ a[i][j];
		printf("%lld ", ans);
	} printf("\n");
	for(int i = 0; i < 2 * m + 1; i ++) {
		int ans = 0;
		for(int j = 0; j < n; j ++) ans = ans ^ a[j][i];
		printf("%lld ", ans);
	} printf("\n");
			
		
//	for(int i = 0; i <= n + m; i ++) printf("%lld ", a[i]);
	return 0; 
}