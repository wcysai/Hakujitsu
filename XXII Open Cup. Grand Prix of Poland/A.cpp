#include<bits/stdc++.h>
#define MAXN 2000005
#define INF 8000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
int T,n,k;
pair<int,int> p[MAXN];
P d[MAXN];
int c[MAXN];
ll get_dist(int x,int y)
{
    return 1LL*(p[x].F-p[y].F)*(p[x].F-p[y].F)+1LL*(p[x].S-p[y].S)*(p[x].S-p[y].S);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) scanf("%d%d",&p[i].F,&p[i].S);
        for(int i=1;i<=n;i++) c[i]=0;
        vector<int> v;
        v.push_back(1); 
        d[1]=P(0,1);
        for(int i=2;i<=n;i++) d[i]=P(get_dist(1,i),1);
        c[1]=1;
        for(int i=2;i<=k;i++)
        {
            int id=-1;
            ll res=-1;
            for(int j=1;j<=n;j++)
            {
                if(!d[j].F) continue;
                if(d[j].F>res)
                {
                    res=d[j].F;
                    id=j;
                }
            }
            //add id into the set']
            
            v.push_back(id);
            c[id]=i;
            for(int i=1;i<=n;i++) d[i]=min(d[i],P(get_dist(id,i),id));
        }
        for(int i=1;i<=n;i++) if(!c[i]) c[i]=c[d[i].S];
        for(int i=1;i<=n;i++) printf("%d%c",c[i],i==n?'\n':' ');
    }
    return 0;
}