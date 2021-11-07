#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
ll a,b,r;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld%lld",&a,&b,&r);
        if(a<=r&&b>=r) printf("%lld %lld\n",r,r+1);
        else if(b>=2*r+1) printf("%lld %lld\n",max(a,2*r+1),max(a,2*r+1)-r);
        else puts("-1 -1");
    }
    return 0;
}