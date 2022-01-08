#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define F first
#define S second
#define double long double
using namespace std;
typedef long long ll;
typedef pair<double,double> P;
int n;
double a[MAXN],b[MAXN],c[MAXN];
const double eps=1e-8;
double calc(double x,double y)
{
    double res=1e18;
    for(int i=0;i<n;i++)
    {
        if(a[i]>0) res=min(res,y-(a[i]*x*x+b[i]*x+c[i]));
        else res=min(res,a[i]*x*x+b[i]*x+c[i]-y);
    }
    return res;
}
pair<double,double> calc_y(double x)
{
    double pores=5e18,neres=5e18;
    for(int i=0;i<n;i++)
    {
        if(a[i]>0) pores=min(pores,-(a[i]*x*x+b[i]*x+c[i]));
        else neres=min(neres,a[i]*x*x+b[i]*x+c[i]);
    }
    if(neres==5e18) return make_pair(calc(x,1e18),1e18);
    else if(pores==5e18) return make_pair(calc(x,-1e18),-1e18); 
    //printf("%.10Lf %.10Lf %.10Lf\n",x,pores,neres);
    return make_pair((pores+neres)/2.0,(neres-pores)/2.0);
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) 
        scanf("%Lf%Lf%Lf",&a[i],&b[i],&c[i]);
    
    double l=1e9,r=-1e9;
    for(int i=0;i<100;i++)
    {
        double lmid=l+(r-l)/3.0,rmid=r-(r-l)/3.0;
        if(calc_y(lmid)>calc_y(rmid)) r=rmid; else l=lmid;
    }
    printf("%.10Lf %.10Lf\n",l,calc_y(l).S);
    return 0;
}