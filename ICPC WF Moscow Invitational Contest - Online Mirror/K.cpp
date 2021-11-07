#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 41
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int p,n,k;
int s[MAXN];
vector<int> v[MAXN];
vector<P> added,deleted;
vector<int> involved;
int cnt[MAXN],delcnt[MAXN],addcnt[MAXN],addedge[MAXN];
vector<int> del,add;
bool dd[MAXN],ad[MAXN],mark[MAXN];
vector<int> basic;
vector<int> opt;
int main()
{
    scanf("%d%d",&p,&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&s[i]);
        v[s[i]].push_back(i);
    }
    scanf("%d",&k);
    for(int i=0;i<k;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(s[x]==s[y]) added.push_back(P(x,y));
        else deleted.push_back(P(x,y));
        involved.push_back(s[x]); involved.push_back(s[y]);
    }
    memset(dd,false,sizeof(dd));
    memset(ad,false,sizeof(ad));
    memset(mark,false,sizeof(mark));
    sort(involved.begin(),involved.end());
    involved.erase(unique(involved.begin(),involved.end()),involved.end());
    for(auto x:involved) 
    {
        cnt[x]=(int)v[x].size();
        mark[x]=true;
    }
    for(int i=1;i<=p;i++) if(!mark[i]) basic.push_back(v[i][0]);
    int ans=0;
    int x=(int)deleted.size(),y=(int)added.size();
    for(int mask1=0;mask1<(1<<x);mask1++)
    {
        del.clear(); 
        for(auto x:involved) delcnt[x]=0;
        for(int i=0;i<x;i++)
        {
            int num;
            if(mask1&(1<<i)) num=deleted[i].F; else num=deleted[i].S;
            if(!dd[num])
            {
                dd[num]=true;
                del.push_back(num);
                delcnt[s[num]]++;
            }
        }
        for(int mask2=0;mask2<(1<<y);mask2++)
        {
            add.clear();
            for(auto x:involved) addcnt[x]=addedge[x]=0;
            for(int j=0;j<y;j++)
            {
                if(!(mask2&(1<<j))) continue;
                if(dd[added[j].F]||dd[added[j].S]) continue;
                int u=added[j].F,v=added[j].S;
                if(!ad[u]) {addcnt[s[u]]++; ad[u]=true; add.push_back(u);}
                if(!ad[v]) {addcnt[s[u]]++; ad[v]=true; add.push_back(v);}
                addedge[s[u]]++;
            }
            //check compatibility
            int sum=p-(int)involved.size();
            bool f=true;
            for(auto v:involved)
            {
                if(addedge[v]!=addcnt[v]*(addcnt[v]-1)/2) {f=false; break;}
                sum+=addcnt[v];
                if(!addcnt[v]&&(cnt[v]-addcnt[v]-delcnt[v])) sum++;
            }
            if(f&&sum>ans) 
            {
                ans=sum; opt=add;
                for(auto x:involved)
                    if(!addcnt[x]&&(cnt[x]-addcnt[x]-delcnt[x]))
                        for(auto xx:v[x]) if(!dd[xx]) {opt.push_back(xx); break;}
            }
            for(auto p:add) ad[p]=false;
        }
        for(auto p:del) dd[p]=false;
    }
    printf("%d\n",ans);
    assert(ans==(int)basic.size()+(int)opt.size());
    opt.insert(opt.end(),basic.begin(),basic.end());
    sort(opt.begin(),opt.end());
    for(auto x:opt) printf("%d ",x);
    puts("");
    return 0;
}