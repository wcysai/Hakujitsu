#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        ll a,b;
        scanf("%lld%lld",&a,&b);
        a=a*2; b=b*360;
        ll g=__gcd(a,b);
        a/=g; b/=g;
        printf("%lld\n",b-1);
    }
    return 0;
}