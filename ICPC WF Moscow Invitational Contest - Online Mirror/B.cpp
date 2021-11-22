#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int p[MAXN],l[MAXN],r[MAXN];
vector<int> comp[MAXN];
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=l[i]=r[i]=i;
        comp[i].push_back(i);
    }
}
int find(int x)
{
    if(p[x]==x) return x;
    else return p[x]=find(p[x]);
}
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y) return;
    p[x]=y;
    l[y]=min(l[x],l[y]); r[y]=max(r[x],r[y]);
}
struct segtree
{
    priority_queue<int> pquesuf[4*MAXN];
    priority_queue<int,vector<int>,greater<int> > pquepre[4*MAXN];
    void update_pre(int k,int l,int r,int p,int pre)
    {
        pquepre[k].push(pre);
        if(l==r) return;
        int mid=(l+r)/2;
        if(p<=mid) update_pre(k*2,l,mid,p,pre); else update_pre(k*2+1,mid+1,r,p,pre);
    }
    void update_suf(int k,int l,int r,int p,int suf)
    {
        pquesuf[k].push(suf);
        if(l==r) return;
        int mid=(l+r)/2;
        if(p<=mid) update_suf(k*2,l,mid,p,suf); else update_suf(k*2+1,mid+1,r,p,suf);
    }
    void query_pre(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y)
        {
            if(!pquepre[k].size()||pquepre[k].top()>=x) return;
            int tmp=pquepre[k].top();
            while(pquepre[k].size()&&pquepre[k].top()<x) 
            {
                unite(x,pquepre[k].top());
                pquepre[k].pop();
            }
            pquepre[k].push(tmp);
            return;
        }
        int mid=(l+r)/2;
        query_pre(k*2,l,mid,x,y); query_pre(k*2+1,mid+1,r,x,y);
    }
    void query_suf(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y)
        {
             if(!pquesuf[k].size()||pquesuf[k].top()<=y) return;
            int tmp=pquesuf[k].top();
            while(pquesuf[k].size()&&pquesuf[k].top()>y) 
            {
                unite(y,pquesuf[k].top());
                pquesuf[k].pop();
            }
            pquesuf[k].push(tmp);
            return;
        }
        int mid=(l+r)/2;
        query_suf(k*2,l,mid,x,y); query_suf(k*2+1,mid+1,r,x,y);
    }
}seg;
string str="";
int main()
{
    scanf("%d%d",&n,&m);
    init(n);
    for(int i=0;i<m;i++)
    {
        int type,u,v;
        scanf("%d%d%d",&type,&u,&v);
        if(type==2)
        {
            u=find(u); v=find(v);
            if(u==v) str+='1'; else str+='0';
        }
        else
        {
            if(find(u)==find(v)) continue;
            if(u>v) swap(u,v);
            unite(u,v);
            seg.query_pre(1,1,n,u,v);
            seg.query_suf(1,1,n,u,v);
            seg.update_pre(1,1,n,v,u); seg.update_suf(1,1,n,u,v);
        }
    }
    cout<<str<<endl;
}