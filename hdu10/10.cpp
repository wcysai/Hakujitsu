#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n[2];
int f[2][4][MAXN];
double g[2][2][MAXN];
const double eps=1e-10;
bool check(int days)
{
    for(int i=0;i<n[1];i++) g[1][0][i]=f[1][0][i];
    for(int i=0;i<n[1];i++) g[1][1][i]=f[1][2][i];
    for(int i=0;i<n[0];i++) g[0][0][i]=f[0][0][i]+1LL*f[0][1][i]*days;
    for(int i=0;i<n[0];i++) g[0][1][i]=f[0][2][i]+1LL*f[0][3][i]*days;
    int x=0,y=0;
    while(x<n[0]&&y<n[1])
    {
        ll need=min((g[0][0][x]-1)/g[1][1][y]+1,(g[1][0][y]-1)/(g[0][1][x]+1));
        g[0][0][x]=max(0LL,g[0][0][x]-g[1][1][y]*need);
        g[0][0][y]=max(0LL,g[0][0][y]-g[1][1][x]*need);
        while(x<n[0]&&g[0][0][x]==0) x++;
        while(y<n[1]&&g[0][0][y]==0) y++;
    }
    if(x==n[0]) return false;
    return true;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n[0],&n[1]);
        for(int i=0;i<2;i++)
            for(int j=0;j<n[i];j++)
                for(int k=0;k<4;k++)
                    scanf("%d",&f[i][k][j]);
        ll l=0,r=2000001;
        while(r-l>1)
        {
            ll mid=(l+r)/2;
            if(check(mid)) l=mid; else r=mid;
        }
        if(l==2000000) puts("none"); else printf("%lld\n",l);
    }
    return 0;
}