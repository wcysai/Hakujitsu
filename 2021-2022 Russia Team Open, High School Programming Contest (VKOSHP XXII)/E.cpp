#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define F first
#define S second
#define double long double
using namespace std;
typedef long long ll;
typedef pair<double,double> P;
int n,a[MAXN];
int premax[MAXN],sufmax[MAXN],premin[MAXN],sufmin[MAXN];
const double eps=1e-9;
double solve(int pmax,int pmin,int smax,int smin,double t)
{
    return (double)max((double)1.0*pmax,((double)1.0-t)*smax)-min((double)1.0*pmin,((double)1.0-t)*smin);
}
P get_min(P x,P y)
{
    if(abs(x.F-y.F)<eps)
    {
        return P(x.F,min(x.S,y.S));
    }
    else return min(x,y);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    premax[0]=sufmax[n+1]=0; premin[0]=sufmin[n+1]=INF+1;
    for(int i=1;i<=n;i++) 
    {
        premax[i]=max(premax[i-1],a[i]);
        premin[i]=min(premin[i-1],a[i]);
    }
    for(int i=n;i>=1;i--)
    {
        sufmax[i]=max(sufmax[i+1],a[i]);
        sufmin[i]=min(sufmin[i+1],a[i]);
    }
    for(int i=1;i<=n;i++)
    {
        int pmax=premax[i-1],smax=sufmax[i],pmin=premin[i-1],smin=sufmin[i];
        pair<double,double> ans=make_pair(INF+1,0);
        ans=get_min(ans,make_pair(solve(pmax,pmin,smax,smin,0),0.0));
        ans=get_min(ans,make_pair(solve(pmax,pmin,smax,smin,1),-1.0));
        if(smax>=pmax) ans=get_min(ans,make_pair(solve(pmax,pmin,smax,smin,1.0-(double)pmax/smax),-1.0+(double)pmax/smax));
        if(smin>=pmin) ans=get_min(ans,make_pair(solve(pmax,pmin,smax,smin,1.0-(double)pmin/smin),-1.0+(double)pmin/smin));
        printf("%.10Lf ",abs(ans.S));
    }
    return 0;
}