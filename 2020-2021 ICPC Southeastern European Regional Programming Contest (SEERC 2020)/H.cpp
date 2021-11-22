#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,a[MAXN],l[MAXN],r[MAXN];
int f[MAXN][31],g[MAXN][31],cnt[MAXN][31];
int tmpf[31],tmpg[31],tmpcnt[31];
void solve(int lb,int rb,vector<int> &queries)
{
    if(lb>=rb||!queries.size()) return;
    vector<int> lhs,rhs,solved;
    int mid=(lb+rb)/2;
    vector<P> lpos,rpos;
    for(auto id:queries) if(r[id]<=mid) lhs.push_back(id); else if(l[id]>mid) rhs.push_back(id); else solved.push_back(id);
    for(auto id:solved)
    {
        //printf("solved id=%d\n",id);
        lpos.push_back(P(l[id],id));
        rpos.push_back(P(r[id],id));
    } 
    sort(lpos.begin(),lpos.end()); sort(rpos.begin(),rpos.end(),greater<P>());
    for(int i=0;i<31;i++) tmpf[i]=2147483647;
     memset(tmpg,0,sizeof(tmpg)); memset(tmpcnt,0,sizeof(tmpcnt));
    for(int i=mid;i>=lb;i--)
    {
        tmpf[__builtin_popcount(a[i])]&=a[i];
        tmpg[__builtin_popcount(a[i])]|=a[i];
        tmpcnt[__builtin_popcount(a[i])]++;
        while(lpos.size()&&lpos.back().F==i) 
        {
            for(int j=0;j<31;j++) f[lpos.back().S][j]&=tmpf[j],g[lpos.back().S][j]|=tmpg[j],cnt[lpos.back().S][j]+=tmpcnt[j];
            lpos.pop_back();
        }
    }
    for(int i=0;i<31;i++) tmpf[i]=2147483647;
     memset(tmpg,0,sizeof(tmpg)); memset(tmpcnt,0,sizeof(tmpcnt));
    for(int i=mid+1;i<=rb;i++)
    {
        tmpf[__builtin_popcount(a[i])]&=a[i];
        tmpg[__builtin_popcount(a[i])]|=a[i];
        tmpcnt[__builtin_popcount(a[i])]++;
        while(rpos.size()&&rpos.back().F==i) 
        {
            for(int j=0;j<31;j++) f[rpos.back().S][j]&=tmpf[j],g[rpos.back().S][j]|=tmpg[j],cnt[rpos.back().S][j]+=tmpcnt[j];
            rpos.pop_back();
        }
    }
    solve(lb,mid,lhs); solve(mid+1,rb,rhs);
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=0;i<q;i++) scanf("%d%d",&l[i],&r[i]);
    for(int i=0;i<q;i++)
        for(int j=0;j<31;j++)
            f[i][j]=2147483647;
    vector<int> v;
    for(int i=0;i<q;i++) v.push_back(i);
    solve(1,n,v);
  //  for(int i=0;i<q;i++) 
       // for(int j=0;j<3;j++)
            //printf("i=%d j=%d f=%d g=%d cnt=%d\n",i,j,f[i][j],g[i][j],cnt[i][j]);
    for(int i=0;i<q;i++)
    {
        int pre[31],suf[31],sum[31];
        pre[0]=g[i][0],sum[0]=cnt[i][0];
        for(int k=1;k<31;k++) pre[k]=(pre[k-1]|g[i][k]),sum[k]=sum[k-1]+cnt[i][k];
        suf[30]=f[i][30];
        for(int k=29;k>=0;k--) suf[k]=(suf[k+1]&f[i][k]);
        bool flag=false;  
        for(int k=0;k<=30;k++)
        {
            if(k!=30&&pre[k]==suf[k+1]&&sum[k]!=0&&sum[k]!=sum[30]) {flag=true; break;}
            if(pre[k]==suf[k]&&__builtin_popcount(f[i][k])==k&&cnt[i][k]>=2) {flag=true; break;}
        }
        if(flag) puts("YES"); else puts("NO");
    }
    return 0;
}