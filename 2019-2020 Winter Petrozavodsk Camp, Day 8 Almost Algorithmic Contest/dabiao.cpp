#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
long double ans=0.0;
int main()
{
    for(int i=400;i<=200000;i++) ans+=1.0/(1LL*i);
    printf("%.10Lf\n",ans);
}