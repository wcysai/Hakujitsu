#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int s=(1<<30);
    for(int i=1;i<=n;i++)
        while(a[i]%s) s>>=1;
    for(int i=1;i<=n;i++) a[i]/=s;
    int mini=INF;
    for(int i=1;i<=n;i++) if(a[i]&1) mini=min(mini,a[i]);
    printf("%d\n",(mini+1)/2);
    return 0;
}