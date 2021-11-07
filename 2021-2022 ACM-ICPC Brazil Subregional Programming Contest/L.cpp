#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 600005
#define MAXLOGN 21
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
char str[MAXN];
int p[MAXLOGN][MAXN],rk[MAXLOGN][MAXN],l[MAXN],r[MAXN];
int pre[MAXN];
int type[MAXN];
void init(int n)
{
    for(int i=0;i<=20;i++)
        for(int j=1;j<=n;j++)
        {
            p[i][j]=j;
            rk[i][j]=0;
        }
}
int find(int k,int x)
{
    if(p[k][x]==x) return x;
    return p[k][x]=find(k,p[k][x]);
}
void unite(int k,int u,int v)
{
    u=find(k,u); v=find(k,v);
    if(u==v) return;
    if(rk[k][u]<rk[k][v]) p[k][u]=v;
    else
    {
        p[k][v]=u;
        if(rk[k][u]==rk[k][v]) rk[k][u]++;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%s",str+1);
    for(int i=1;i<=n;i++) str[n+i]=str[n-i+1];
    init(2*n);
    pre[1]=0;
    for(int i=2;i<=n;i++)
    {
        pre[i]=pre[i-1];
        if ((1<<pre[i]+1)==i) ++pre[i];
    }
    for(int i=0;i<m;i++) 
    {
        scanf("%d%d",&l[i],&r[i]);
        int l1=l[i],r1=r[i],l2=n+(n-r[i]+1),r2=l2+(r[i]-l[i]);
        int len=r[i]-l[i]+1,k=pre[len];
        unite(k,l1,l2);
        unite(k,r1-(1<<k)+1,r2-(1<<k)+1);
    }
    for(int k=20;k>=1;k--)
    {
        for(int i=1;i+(1<<k)-1<=2*n;i++)
        {
            unite(k-1,i,find(k,i));
            unite(k-1,i+(1<<(k-1)),find(k,i)+(1<<(k-1)));
        }
    }
    for(int i=1;i<=n;i++) unite(0,i,2*n+1-i);
    int ans=1;
    for(int i=1;i<=2*n;i++)
    {
        //printf("i=%d pos=%d\n",i,find(0,i));
        if(str[i]=='?') continue;
        int pos=find(0,i);
        if(type[pos]==0) type[pos]=str[i]-'0'+1;
        else if(type[pos]!=str[i]-'0'+1) ans=0;
    }
    for(int i=1;i<=2*n;i++) if(find(0,i)==i&&type[i]==0) ans=2LL*ans%MOD;
    printf("%d\n",ans);
    return 0;
}