#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
#define lc t[x].ch[0]
#define rc t[x].ch[1]
#define pa t[x].fa
typedef long long ll;
typedef pair<ll,ll> P;
ll sum;
int getint()

 {

    char ch = getchar();

    for ( ; ch > '9' || ch < '0'; ch = getchar());

    int tmp = 0;

    for ( ; '0' <= ch && ch <= '9'; ch = getchar())

      tmp = tmp * 10 + int(ch) - 48;

    return tmp;

 } 
namespace lct 
{
    struct meow{int ch[2], fa, rev, id, w; ll maxi;} t[2*MAXN];
    inline int wh(int x) {return t[pa].ch[1] == x;}
    inline int isr(int x) {return t[pa].ch[0] != x && t[pa].ch[1] != x;}
    inline void update(int x) 
    {
        t[x].id=x; t[x].maxi=t[x].w;
        if(t[lc].maxi>t[x].maxi) t[x].maxi=t[lc].maxi,t[x].id=t[lc].id;
        if(t[rc].maxi>t[x].maxi) t[x].maxi=t[rc].maxi,t[x].id=t[rc].id;
    }
    inline void rever(int x) {t[x].rev ^= 1; swap(lc, rc);}
    inline void pushdown(int x) 
    {
        if(t[x].rev) 
        {
            if(lc) rever(lc);
            if(rc) rever(rc);
            t[x].rev = 0;
        }
    }
    void pd(int x) {if(!isr(x)) pd(pa); pushdown(x);}
    inline void rotate(int x) 
    {
        int f=t[x].fa, g=t[f].fa, c=wh(x);
        if(!isr(f)) t[g].ch[wh(f)]=x; 
        t[x].fa=g;
        t[f].ch[c] = t[x].ch[c^1]; t[t[f].ch[c]].fa=f;
        t[x].ch[c^1] = f; t[f].fa=x;
        update(f); update(x);
    }
    inline void splay(int x) 
    {
        pd(x);
        for(; !isr(x); rotate(x))
            if(!isr(pa)) rotate( wh(pa)==wh(x) ? pa : x );
    }

    inline void access(int x) 
    {
        for(int y=0; x; y=x, x=pa) splay(x), rc=y, update(x);
    }
    inline void maker(int x) 
    {
        access(x); splay(x); rever(x);
    }
    inline int findr(int x) 
    {
        access(x); splay(x);
        while(lc) pushdown(x), x=lc; 
        return x;
    }
    inline void link(int x, int y) 
    {
        maker(x); 
        if(findr(y)!=x) t[x].fa=y;
    }
    inline void cut(int x, int y) 
    {
        maker(x);
        if(findr(y)==x&&t[x].fa==y&&t[y].ch[0]==x&&!t[y].ch[1])
        {
            t[x].fa=t[y].ch[0]=0; 
            update(y);
        }
    }
    inline void split(int x, int y) 
    {
        maker(x); access(y); splay(y);
    }
};

int n,m,q;
P E[MAXN];
int tot;
bool add_edge(int u,int v,ll w)
{
    if(lct::findr(u)!=lct::findr(v)) 
    {
        tot++;
        lct::link(u,tot);lct::link(v,tot);
        lct::t[tot].w=w;lct::splay(tot);
        //printf("added %dth edge from %d to %d with weight %d\n",tot-n,u,v,w);
        sum+=w;
        E[tot]=P(u,v);
        return true;
    }
    else
    {
        lct::split(u,v);
        int id=lct::t[v].id;
        ll ww=lct::t[v].maxi;
        if(ww>w)
        {
            lct::cut(id,E[id].F);lct::cut(id,E[id].S);
            //printf("cut %dth edge from %d to %d with weight %d\n",tot-n,u,v,ww);
            tot++;
            lct::link(u,tot);lct::link(v,tot);
            //printf("added %dth edge from %d to %d with weight %d\n",tot-n,u,v,w);
            lct::t[tot].w=w;lct::splay(tot);
            E[tot]=P(u,v);
            sum+=w; sum-=ww;
            return true;
        }
    }
    return false;
}
vector<pair<P,P> > edges;
vector<P> queries;
vector<pair<P,P> > events;
ll ans[MAXN];
int main() 
{
    n=getint();m=getint();
    for(int i=0;i<m;i++) 
    {
       int u,v,w,c;
       u=getint(); v=getint(); w=getint(); c=getint();
       edges.push_back(make_pair(P(u,v),P(w,c)));
    }
    q=getint();
    for(int i=0;i<q;i++)
    {
        int k;
        k=getint();
        queries.push_back(P(k,i));
    }
    sort(queries.begin(),queries.end());
    for(int i=0;i<m;i++)
    {
        int x=edges[i].S.F;
        for(int j=1;j<=1000000;j+=x)
        {
            int l=j,r=min(1000000,j+x-1);
            int id=lower_bound(queries.begin(),queries.end(),P(l,-1))-queries.begin();
            if(id<(int)queries.size()&&queries[id].F<=r)
            {
                events.push_back(make_pair(P(r,1LL*edges[i].S.S*((l+x-1)/x)),edges[i].F));
            }
        }
    }
    reverse(queries.begin(),queries.end());
    sort(events.begin(),events.end());
    reverse(events.begin(),events.end());
    sum=0;
    int now=0;
    tot=n;
    for(int i=0;i<q;i++)
    {
        while(now<(int)events.size()&&events[now].F.F>=queries[i].F) 
        {
            if(!add_edge(events[now].S.F,events[now].S.S,events[now].F.S));
            now++;
        }
        ans[queries[i].S]=sum;
    }
    for(int i=0;i<q;i++) printf("%lld\n",ans[i]);
    return 0;
}
