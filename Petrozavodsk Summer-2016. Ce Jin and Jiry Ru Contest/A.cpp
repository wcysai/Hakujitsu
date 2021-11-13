#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,m,a[MAXN],b[MAXN];
vector<int> posa[MAXN],posb[MAXN];
int r[MAXN],id[MAXN];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n;i++) posa[i].clear(),posb[i].clear();
        for(int i=1;i<=n;i++) 
        {
            scanf("%d",&a[i]);
            posa[a[i]].push_back(i);
        }
        for(int i=1;i<=n;i++) 
        {
            scanf("%d",&b[i]);
            posb[b[i]].push_back(i);
        }
        bool f=true;
        for(int i=0;i<=n;i++)
        {
            if((int)posa[i].size()!=(int)posb[i].size())
            {
                f=false;
                break;
            }
        }
        if(f)
        {
            memset(id,0,sizeof(id));
            for(int i=1;i<=n;i++)
            {
                int val=b[i];
                r[posa[val][id[val]]]=i;
                id[val]++;
            }
        }
        else memset(r,0,sizeof(r));
        for(int i=0;i<m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            sort(r+u,r+v+1);
        }
        for(int i=1;i<=n;i++) if(r[i]!=i) f=false;
        if(f) puts("Yes"); else puts("No");
    }
    return 0;
}