#include<bits/stdc++.h>
using namespace std;
 
#define rep(i,n) for (int i=0;i<(int)(n);++i)
#define rep1(i,n) for (int i=1;i<=(int)(n);++i)
#define range(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int maxn=3007;
int n,p;
int a[maxn],C[maxn][maxn],f[maxn],g[maxn];

int main(){
	int _;
	scanf("%d",&_);
	while (_--)
    {
		scanf("%d%d",&n,&p);
		C[0][0]=1%p;
		f[0]=g[0]=1%p;
		for (int i=1;i<=3000;++i){
			C[i][0]=1%p;
			for (int j=1;j<=i;++j){
				C[i][j]=(C[i-1][j]+C[i-1][j-1])%p;
			}
		}
		memset(a,0,sizeof(a));
		int ans=1%p;
		a[1]=n%p;
		for (int mx=2;mx<=n;++mx)
        {
            if(mx==n)
            {
                ans=(ans+1)%p;
                for (int j=1;j<=mx;++j) a[j]=(a[j]+1)%p;
                continue;	
            }
			int tmp=0;
			for (int i=1;i<=3000;++i){
				f[i]=1LL*(mx-1)*f[i-1]%p, g[i]=1LL*mx*g[i-1]%p;
			}
			for (int pos=1;pos<=n;++pos)
            {
				if (n-pos<mx-1) continue;
				tmp=(tmp+(1LL*C[n-pos][mx-1]*f[n-pos+1-mx]%p)*g[pos-1])%p;
			}
			// cout<<endl;
			ans=(ans+tmp)%p;
            tmp=0;
            for (int pos=1;pos<=n;++pos)
            {
				if (n-pos<mx-1) continue;
				if(pos>1) tmp=(tmp+(1LL*C[n-pos][mx-1]*f[n-pos+1-mx]%p)*g[pos-2]%p*n)%p;
                else tmp=(tmp+(1LL*C[n][mx]*f[n-pos+1-mx]%p)*g[pos-1])%p;
			}
			for (int j=1;j<=mx;++j){
				a[j]=(a[j]+tmp)%p;	
			}
		}
		printf("%d\n",ans);
		for(int i=1;i<=n;i++) printf("%d%c",a[i],i==n?'\n':' ');
	}
	
}
