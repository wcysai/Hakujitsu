#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,a[MAXN],b[MAXN];
int sufa[MAXN],sufb[MAXN];
P v1[MAXN],v2[MAXN];
int get_valb(int x)
{
    int pos=lower_bound(v1+1,v1+n+1,P(x,0))-v1;
    return sufa[pos];
}
int get_vala(int x)
{
    int pos=lower_bound(v2+1,v2+n+1,P(x,0))-v2;
    return sufb[pos];
}
int main()
{
    scanf("%d",&t);
    
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) scanf("%d",&b[i]);
        for(int i=1;i<=n;i++) v1[i]=P(a[i],b[i]),v2[i]=P(b[i],a[i]);
        sort(v1+1,v1+n+1); sort(v2+1,v2+n+1);
        sufa[n+1]=sufb[n+1]=INF+1;
        for(int i=n;i>=1;i--) sufa[i]=min(sufa[i+1],v1[i].S);
        for(int i=n;i>=1;i--) sufb[i]=min(sufb[i+1],v2[i].S);
        int cura=v1[n].F,curb=v2[n].F;
        while(true)
        {
            if(get_valb(cura)<curb) curb=get_valb(cura);
            else if(get_vala(curb)<cura) cura=get_vala(curb);
            else break;
        }
        for(int i=1;i<=n;i++) if(a[i]>=cura||b[i]>=curb) puts("YES"); else puts("NO");
    }
    return 0;
}