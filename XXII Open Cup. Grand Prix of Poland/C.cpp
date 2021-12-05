#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,tot,n,a[2][MAXN],b[2][MAXN];
map<P,int> mp;
vector<int> pos[MAXN];
int perm[MAXN];
int get_id(P p)
{
    if(mp.find(p)==mp.end()) mp[p]=++tot;
    return mp[p];
}
int bit[MAXN+1];
int sum(int i)
{
    int s=0;
    while(i>0)
    {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(int i,int x)
{
    while(i<=n)
    {
        bit[i]+=x;
        i+=i&-i;
    }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        for(int i=1;i<=tot;i++) pos[i].clear();
        tot=0;
        mp.clear();
        scanf("%d",&n);
        for(int i=1;i<=n;i++) bit[i]=0;
        for(int i=0;i<2;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",&a[i][j]);
        for(int i=0;i<2;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",&b[i][j]);
        for(int i=1;i<=n;i++)
        {
            P p;
            if(i&1) p=make_pair(a[0][i],a[1][i]); else p=make_pair(a[1][i],a[0][i]);
            pos[get_id(p)].push_back(i);
        }
        for(int i=1;i<=tot;i++) reverse(pos[i].begin(),pos[i].end());
        bool f=true;
        for(int i=1;i<=n;i++)
        {
            P p;
            if(i&1) p=make_pair(b[0][i],b[1][i]); else p=make_pair(b[1][i],b[0][i]);
            if(mp.find(p)==mp.end())
            {
                f=false;
                break;
            }
            if(!pos[mp[p]].size())
            {
                f=false;
                break;
            }
            perm[i]=pos[mp[p]].back();
            pos[mp[p]].pop_back();
        }
        if(!f)
        {
            puts("-1");
            continue;
        }
        ll ans=0;
        for(int i=1;i<=n;i++) 
        {
            ans+=(i-1)-sum(perm[i]);
            add(perm[i],1);
        }
        printf("%lld\n",ans);
    }
    return 0;
}