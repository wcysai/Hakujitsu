#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,u[MAXN],v[MAXN],w[MAXN];
vector<int> G[MAXN];
int p[MAXN],r[MAXN],val[MAXN];
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        val[i]=0;
        r[i]=1;
    }
}
P find(int x)
{
    if(p[x]==x) return P(0,x);
    P pp=find(p[x]);
    return P(val[x]^pp.F,pp.S);
}
void unite(int u,int v)
{
    //printf("unite %d %d\n",u,v);
    P pu=find(u); P pv=find(v);
    u=pu.S; v=pv.S;
    if(u!=v) 
    {
        if(r[u]<r[v])
        {
            p[u]=v;
            if(pu.F==pv.F) val[u]=1; else val[u]=0;
        }
        else
        {
            p[v]=u;
            if(pu.F==pv.F) val[v]=1; else val[v]=0;
            if(r[u]==r[v]) r[u]++;
        }
    } 
    //for(int i=1;i<=4;i++) printf("%d %d %d\n",i,find(i).F,find(i).S);
}
vector<int> dis;
vector<P> edges[MAXN];
vector<int> ans;
int confs[2*MAXN],conft[2*MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%d",&u[i],&v[i],&w[i]);
        dis.push_back(w[i]);
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    for(int i=0;i<m;i++)
    {
        int id=lower_bound(dis.begin(),dis.end(),w[i])-dis.begin();
        edges[id].push_back(P(u[i],v[i]));
    }
    int sz=(int)dis.size();
    init(n);
    bool f=true;
    for(int i=sz-1;i>=0;i--)
    {
        //printf("i=%d\n",i);
        if(!f) break; 
        int bad=0;
        set<P> tmp; vector<P> vv;
        for(auto p:edges[i])
        {
            P pu=find(p.F),pv=find(p.S);
            int u=pu.S,v=pv.S,cu=pu.F,cv=pv.F;
            if(u>v) swap(u,v),swap(cu,cv);
            //printf("p.F=%d p.S=%d u=%d v=%d valu=%d valv=%d\n",p.F,p.S,u,v,cu,cv);
            if(u==v)
            {
                if(cu!=cv);
                else 
                {
                    vv.push_back(p);
                    //confs[n*(1-cu)+u]++;
                    //conft[n*cu+u]++;
                }
            }
            else
            {
                //s: u must be val[p.F] v must be val[p.S]  
               // confs[n*(1-cu)+u]++; confs[n*(1-cv)+v]++; confs2[P(n*(1-cu)+u,n*(1-cv)+v)]++;
               // conft[n*cu+u]++; conft[n*cv+v]++; conft2[P(n*cu+u,n*cv+v)]++;
               if(!tmp.count(P(n*cu+u,n*cv+v)))
               {
                   vv.push_back(p);
                   tmp.insert(P(n*cu+u,n*cv+v));
               }
            }
        }
        int esz=(int)vv.size();
        //printf("esz=%d\n",esz);
        for(auto p:vv)
        {
            P pu=find(p.F),pv=find(p.S);
            int u=pu.S,v=pv.S,cu=pu.F,cv=pv.F;
            if(u>v) swap(u,v),swap(cu,cv);
            //printf("p.F=%d p.S=%d u=%d v=%d valu=%d valv=%d\n",p.F,p.S,u,v,cu,cv);
            if(u==v)
            {
                confs[n*(1-cu)+u]++;
                conft[n*cu+u]++;
            }
            else
            {
                //s: u must be val[p.F] v must be val[p.S]  
                confs[n*(1-cu)+u]++; confs[n*(1-cv)+v]++; 
                conft[n*cu+u]++; conft[n*cv+v]++; 
            }
        }
        bool flag=false;
        for(auto p:vv)
        {
            P pu=find(p.F),pv=find(p.S);
            int u=pu.S,v=pv.S,cu=pu.F,cv=pv.F;
            if(u>v) swap(u,v),swap(cu,cv);
            if(u==v)
            {
                if(cu!=cv) continue;
                else
                {
                    //try to be s
                    int conflict=bad;
                    int flip=cu;
                    conflict+=conft[n*flip+u];
                    if(conflict<esz) flag=true;
                    //try to be t
                    conflict=bad;
                    flip=1-cu;
                    conflict+=confs[n*flip+u];
                    if(conflict<esz) flag=true;
                }
            }
            else
            {
                //try to be s
                int conflict=bad;
                int flipu=cu,flipv=cv;
                conflict+=conft[n*flipu+u]+conft[n*flipv+v];
                // printf("conflict=%d\n",conflict);
                if(conflict<esz+1) flag=true;
                //try to be t
                conflict=bad;
                flipu=1-cu,flipv=1-cv;
                conflict+=confs[n*flipu+u]+confs[n*flipv+v];
                //printf("conflict=%d\n",conflict);
                if(conflict<esz+1) flag=true;
            }
        }
        if(flag) ans.push_back(dis[i]);
        for(auto p:vv)
        {
            P pu=find(p.F),pv=find(p.S);
            int u=pu.S,v=pv.S,cu=pu.F,cv=pv.F;
            if(u>v) swap(u,v),swap(cu,cv);
            if(u==v)
            {
                if(cu!=cv);
                else 
                {
                    confs[n*(1-cu)+u]--;
                    conft[n*cu+u]--;
                }
            }
            else
            {
                //s: u must be val[p.F] v must be val[p.S]  
                confs[n*(1-cu)+u]--; confs[n*(1-cv)+v]--; 
                conft[n*cu+u]--; conft[n*cv+v]--; 
            }
        }
        for(auto p:edges[i])
        {
            P pu=find(p.F),pv=find(p.S);
            int u=pu.S,v=pv.S,cu=pu.F,cv=pv.F;
            if(u==v)
            {
                if(cu==cv) 
                {
                    f=false;
                    break;
                }
            }
            else unite(p.F,p.S);
        }
    }
    if(f) ans.push_back(0);
    if(ans.size()==0) {puts("IMPOSSIBLE"); return 0;}
    sort(ans.begin(),ans.end());
    for(auto x:ans) printf("%d\n",x);
    return 0;
}
/*
9 7
1 2 3
2 3 3
3 4 3
1 3 2
2 4 2
6 7 1
8 9 1
*/