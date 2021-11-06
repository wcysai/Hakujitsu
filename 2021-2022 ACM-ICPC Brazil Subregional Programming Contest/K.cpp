#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,d,m,y[MAXN];
int main()
{
    scanf("%d%d%d",&t,&d,&m);
    y[0]=0; y[m+1]=d;
    for(int i=1;i<=m;i++) scanf("%d",&y[i]);
    bool f=false;
    for(int i=1;i<=m+1;i++) if(y[i]-y[i-1]>=t) f=true;
    if(f) puts("Y"); else puts("N");
    return 0;
}