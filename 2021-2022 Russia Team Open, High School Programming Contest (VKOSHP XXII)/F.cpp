#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int a,b,c,d,e,f,g;
int main()
{
    scanf("%d%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f,&g);
    printf("%lld\n",(1LL*a*b+1LL*c*d)*e*f*g);
    return 0;
}