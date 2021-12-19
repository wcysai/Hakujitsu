#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%n;
        a=1LL*a*a%n;
        i>>=1;
    }
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;i++) if(pow_mod(i,(n-1)/2)==1) printf("1 "); else printf("0 ");
    return 0;
}