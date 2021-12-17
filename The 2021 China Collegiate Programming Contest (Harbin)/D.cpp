#include<bits/stdc++.h>
#define MAXN 2000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,tot;
ll p,q;
vector<int> vp,vq;
map<ll,int> mp;
set<ll> s[MAXN];
int cnt[20];

ll get_hash()
{
    ll now=0;
    for(int i=0;i<=9;i++)
        for(int j=0;j<cnt[i];j++) 
            now=now*11+(i+1);
    return now;
}
int get_id(ll x)
{
    if(mp.find(x)==mp.end()) mp[x]=++tot;
    return mp[x];
}
__int128 a,b;
int main()
{
    scanf("%d",&n);
    while(n--)
    {
        scanf("%lld%lld",&p,&q);
        for(int i=0;i<=tot;i++) s[i].clear();
        tot=0; mp.clear();
        ll tmpp=p,tmpq=q;
        vp.clear(); vq.clear();
        while(tmpp)
        {
            vp.push_back(tmpp%10);
            tmpp/=10;
        } 
        while(tmpq)
        {
            vq.push_back(tmpq%10);
            tmpq/=10;
        } 
        reverse(vp.begin(),vp.end()); reverse(vq.begin(),vq.end());
       /* for(auto x:vp) printf("%d ",x);
        puts("");
        for(auto x:vq) printf("%d ",x);
        puts("");*/
        int szp=(int)vp.size(),szq=(int)vq.size();
        for(int mask=1;mask<(1<<szq);mask++)
        {
            memset(cnt,0,sizeof(cnt));
            ll val=0;
            for(int j=0;j<szq;j++)
            {
                if(mask&(1<<j))
                {
                    val=val*10+vq[j];
                }
                else cnt[vq[j]]++;
            }
            if(val==0) continue;
            ll h=get_hash();
            int id=get_id(h);
            s[id].insert(val);
        }
        ll x=p,y=q;
        for(int mask=1;mask<(1<<szp);mask++)
        {
            memset(cnt,0,sizeof(cnt));
            ll val=0;
            for(int j=0;j<szp;j++)
            {
                if(mask&(1<<j))
                {
                    val=val*10+vp[j];
                }
                else cnt[vp[j]]++;
            }
            if(val==0||val>=x) continue;
            ll h=get_hash();
            int id=get_id(h);
            a=(__int128)q*(__int128)val;
            if(a%((__int128)p)==0) b=a/(__int128)p; else continue;
            ll res=(ll)b;
            if(s[id].count(res)) {x=val; y=res;}
        }
        printf("%lld %lld\n",x,y);
    }
    return 0;
}

/*
2
121212 121212
121121 121
*/