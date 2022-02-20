#include<bits/stdc++.h>
#define MAXN 100005
#define MAXV 400005
#define MAXM 5
#define INF 1000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
int n=10;
ll x=INF/10;
mt19937 wcy(time(NULL));
int main()
{
    freopen("F.in","w",stdout);
    printf("%d %lld\n",n,x);
    for(int i=0;i<n;i++) printf("%d ",wcy()%1000000001);
    return 0;
}