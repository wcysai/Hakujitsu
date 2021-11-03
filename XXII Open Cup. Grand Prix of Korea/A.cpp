#include<bits/stdc++.h>
#define MAXN 1005
#define INF 4000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef pair<int,int> P;
typedef long long ll;
int n;
ll a[MAXN][MAXN];
ll rd[MAXN],cd[MAXN];
ll r[MAXN],c[MAXN];
ll coef[MAXN];
ll ans[MAXN][MAXN];
multiset<ll> s;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%lld",&a[i][j]);
    for(int i=2;i<=n;i++) cd[i]=a[1][i]-a[1][i-1];
    for(int i=2;i<=n-1;i++) c[i]=(cd[i+1]-cd[i])/2;
    for(int i=2;i<=n;i++) rd[i]=a[i][1]-a[i-1][1];
    for(int i=2;i<=n-1;i++) r[i]=(rd[i+1]-rd[i])/2;
    ll sc=0,sr=0;
    for(int i=2;i<=n-1;i++) sc+=c[i],sr+=r[i];
    ll dc,dr;
    dc=cd[n]-sc,dr=rd[n]-sr;//dc=c[1]-c[n],dr=r[1]-r[n]
    ll x=(sc-dc+dr-sr)/2;//x=r[1]-c[1]
    ll sum=n*(sc+sr);
    for(int i=2;i<=n-1;i++) sum-=1LL*i*r[i],sum-=1LL*i*c[i];
    sum=a[n][n]-sum;
    sum/=n-1;//sum=r[1]+c[1]
    r[1]=(sum+x)/2; c[1]=sum-r[1];
    r[n]=r[1]-dr; c[n]=c[1]-dc;
    for(int i=1;i<=n;i++) s.insert(r[i]);
    for(int i=1;i<=n;i++) s.insert(c[i]);
    memset(ans,-1,sizeof(ans));
    int filled=0;
    while(filled<n*n)
    {
        ll mini=*s.begin();
        P p=P(-1,-1);
        for(int i=1;i<=n;i++)
            if(r[i]==mini)
                p=P(0,i);
        for(int i=1;i<=n;i++)
            if(c[i]==mini)
                p=P(1,i);
        if(p.F==0)
        {
            int id=-1;
            for(int j=1;j<=n;j++) if(ans[p.S][j]==-1) {id=j; break;}
            for(int j=1;j<=n;j++)
            {
                if(ans[p.S][j]!=-1) continue;
                if(j==id)
                {
                    s.erase(s.find(c[j]));
                    c[j]-=mini;
                    s.insert(c[j]);
                    ans[p.S][j]=mini;
                }
                else ans[p.S][j]=0;
                filled++;
            }
            r[p.S]=INF;
            s.erase(s.find(mini));
        }
        else
        {
            int id=-1;
            for(int j=1;j<=n;j++) if(ans[j][p.S]==-1) {id=j; break;}
            for(int j=1;j<=n;j++)
            {
                if(ans[j][p.S]!=-1) continue;
                if(j==id)
                {
                    s.erase(s.find(r[j]));
                    r[j]-=mini;
                    s.insert(r[j]);
                    ans[j][p.S]=mini;
                }
                else ans[j][p.S]=0;
                filled++;
            }
            c[p.S]=INF;
            s.erase(s.find(mini));
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            printf("%lld%c",ans[i][j],j==n?'\n':' ');
    return 0;
}