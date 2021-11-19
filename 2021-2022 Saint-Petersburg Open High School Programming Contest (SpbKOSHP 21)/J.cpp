#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll l,r;
ll get_rev(ll x)
{
    vector<int> v;
    while(x)
    {
        v.push_back(x%10);
        x/=10;
    }
    reverse(v.begin(),v.end());
    ll y=0;
    while(v.size())
    {
        y=y*10+v.back();
        v.pop_back();
    }
    return y;
}
bool is_sqr(ll x)
{
    int d=sqrt(x);
    d--;
    while(1LL*(d+1)*(d+1)<=x) d++;
    return 1LL*d*d==x;
}
int main()
{
    scanf("%lld%lld",&l,&r);
    ll ans=0;
    for(int i=1;1LL*i*i<=r;i++)
    {
        if(1LL*i*i<l) continue;
        if(1LL*i*i%10==0) continue;
        if(is_sqr(get_rev(1LL*i*i))) ans++;
    }
    printf("%lld\n",ans);
    return 0;
}