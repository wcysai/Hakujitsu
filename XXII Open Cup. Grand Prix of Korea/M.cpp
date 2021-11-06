#include<bits/stdc++.h>
#define MAXN 150005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,a[MAXN];
int Lmin[MAXN],Rmin[MAXN],Lmax[MAXN],Rmax[MAXN];
vector<pair<P,int> > update[MAXN];
vector<pair<P,P> > query[MAXN];
int st[MAXN],curid;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
struct mat
{
    int a[2][2];
    mat() {memset(a,0,sizeof(a));}
};
struct vec
{
    int a[2];
    vec() {memset(a,0,sizeof(a));}
};
mat operator*(mat &a,mat &b)
{
    mat c;
    for(int i=0;i<2;i++)
        for(int k=0;k<2;k++)
        {
            if(!a.a[i][k]) continue;
            for(int j=0;j<2;j++)
                add(c.a[i][j],1LL*a.a[i][k]*b.a[k][j]%MOD);
        }
    return c;
}
bool operator!=(mat &a,mat &b)
{
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            if(a.a[i][j]!=b.a[i][j]) return true;
    return false;
}
vec operator*(mat &a,vec &b)
{
    vec c;
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            add(c.a[i],1LL*a.a[i][j]*b.a[j]%MOD);
    return c;
}
mat id;
struct segtree
{
    vec ans[4*MAXN];
    mat tag[4*MAXN];
    void pushup(int k)
    {
        for(int i=0;i<2;i++) 
        {
            ans[k].a[i]=ans[k*2].a[i];
            add(ans[k].a[i],ans[k*2+1].a[i]);
        }
    }
    void pushdown(int k)
    {
        if(tag[k]!=id)
        {
            for(int i=k*2;i<=k*2+1;i++) 
            {
                tag[i]=tag[k]*tag[i];
                ans[i]=tag[k]*ans[i];
            }
            tag[k]=id;
        }
    }
    void build(int k,int l,int r)
    {
        tag[k]=id;
        if(l==r) 
        {
            ans[k].a[0]=1; 
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int x,int y,mat &a)
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y) 
        {
            tag[k]=a*tag[k];
            ans[k]=a*ans[k];
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,a); update(k*2+1,mid+1,r,x,y,a);
        pushup(k);
    }
    vec query_hsum(int k,int l,int r,int x,int y)
    {
        vec v;
        if(l>y||x>r) return v;
        if(l>=x&&r<=y) return ans[k];
        pushdown(k);
        int mid=(l+r)/2;
        vec ls=query_hsum(k*2,l,mid,x,y),rs=query_hsum(k*2+1,mid+1,r,x,y);
        v.a[0]=ls.a[0]; add(v.a[0],rs.a[0]); 
        v.a[1]=ls.a[1]; add(v.a[1],rs.a[1]);
        return v;
    }
}seg;
int ans[MAXN];

int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int main()
{
    id.a[0][0]=id.a[1][1]=1;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int t=0;
	for(int i=1;i<=n;i++)
	{
		while(t>0&&a[st[t-1]]>=a[i]) t--;
		Lmin[i]=t==0?0:st[t-1];
		st[t++]=i;
	}
	t=0;
	for(int i=n;i>=1;i--)
	{
		while(t>0&&a[st[t-1]]>=a[i]) t--;
		Rmin[i]=t==0?n+1:st[t-1];
		st[t++]=i;
	}
    t=0;
	for(int i=1;i<=n;i++)
	{
		while(t>0&&a[st[t-1]]<=a[i]) t--;
		Lmax[i]=t==0?0:st[t-1];
		st[t++]=i;
	}
	t=0;
	for(int i=n;i>=1;i--)
	{
		while(t>0&&a[st[t-1]]<=a[i]) t--;
		Rmax[i]=t==0?n+1:st[t-1];
		st[t++]=i;
	}
    //for(int i=1;i<=n;i++) printf("%d %d %d %d\n",Lmin[i],Rmin[i],Lmax[i],Rmax[i]);
    for(int i=1;i<=n;i++)
    {
        int inv=pow_mod(a[i],MOD-2);
        update[Lmin[i]+1].push_back(make_pair(P(i,Rmin[i]-1),a[i]));
        update[i+1].push_back(make_pair(P(i,Rmin[i]-1),inv));
        update[Lmax[i]+1].push_back(make_pair(P(i,Rmax[i]-1),a[i]));
        update[i+1].push_back(make_pair(P(i,Rmax[i]-1),inv));
    }
    seg.build(1,1,n); 
    for(int i=0;i<q;i++)
    {
        int l,r,s,e;
        scanf("%d%d%d%d",&l,&r,&s,&e);
        query[r].push_back(make_pair(P(s,e),P(i,1)));
        query[l-1].push_back(make_pair(P(s,e),P(i,-1)));
    }
    for(int i=1;i<=n;i++)
    {
        //printf("i=%d\n",i);
        for(auto p:update[i]) 
        {
            //printf("update %d %d %d\n",p.F.F,p.F.S,p.S);
            mat a;
            a.a[0][0]=p.S; a.a[1][1]=1; a.a[1][0]=1LL*(MOD-p.S+1)*(i-1)%MOD; 
            seg.update(1,1,n,p.F.F,p.F.S,a);
        }
        for(auto p:query[i])
        {
            vec v=seg.query_hsum(1,1,n,p.F.F,p.F.S);
            //printf("query %d %d %d %d\n",p.F.F,p.F.S,v.a[0],v.a[1]);
            int res=1LL*i*v.a[0]%MOD; add(res,v.a[1]%MOD);
            if(p.S.S==1) add(ans[p.S.F],res);
            else dec(ans[p.S.F],res);
        }
        if(i>0) 
        {
            mat a;
            a.a[0][0]=0; a.a[1][1]=1; a.a[1][0]=i; 
            seg.update(1,1,n,i,i,a);
        }
    }
    for(int i=0;i<q;i++) printf("%d\n",ans[i]);
    return 0;
}