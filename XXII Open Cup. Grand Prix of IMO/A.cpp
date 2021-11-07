#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,a[MAXN];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        bool f=true;
        for(int i=1;i<=n;i++) if((a[i]&a[1])!=a[1]) f=false;
        if(!f) {puts("-1"); continue;}
        printf("%d\n",2*n-1);
        printf("%d",a[1]);
        for(int i=2;i<=n;i++) printf(" %d %d",a[i],a[1]);
        puts("");
    }
    return 0;
}