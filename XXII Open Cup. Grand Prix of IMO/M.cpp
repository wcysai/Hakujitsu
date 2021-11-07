#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,cnt[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        cnt[x]++;
    }
    ll ans=0;
    for(int i=1;i<=1000;i++)
        //b=2ai+i^2
        for(int j=1;2LL*j*i+1LL*i*i<=1000000;j++)
            if(cnt[j]&&cnt[2LL*j*i+1LL*i*i]) ans++;
    printf("%lld\n",ans);
    return 0;
}