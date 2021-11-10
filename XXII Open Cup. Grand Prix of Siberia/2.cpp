#include<bits/stdc++.h>
#define MAXN 205
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<double,double> P;
typedef pair<double,int> PP;
int n,r,x[MAXN],y[MAXN];
const double PI=acos(-1.0);
vector<P> points[MAXN];
vector<pair<int,double> > G[1000005];
double d[1000005];
double get_dist(P x,P y)
{
    return sqrt((x.F-y.F)*(x.F-y.F)+(x.S-y.S)*(x.S-y.S));
}
void go()
{
    fill(d,d+200*n,1e12);
    for(int i=0;i<200;i++) d[i]=0;
    for(int i=0;i<n-1;i++)
        for(int j=0;j<200;j++)
            for(int k=0;k<200;k++)
                d[(i+1)*200+k]=min(d[(i+1)*200+k],d[i*200+j]+get_dist(points[i][j],points[i+1][k]));
}
int main()
{
    scanf("%d%d",&n,&r);
    for(int i=0;i<n;i++) scanf("%d%d",&x[i],&y[i]);
    if(n==2)
    {
        printf("%.10f\n",get_dist(P(x[0],y[0]),P(x[1],y[1]))-2*r);
        return 0;
    } 
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<200;j++)
        {
            double dx=x[i]+1.0*r*cos(2*PI/200*j);
            double dy=y[i]+1.0*r*sin(2*PI/200*j);
            points[i].push_back(P(dx,dy));
        }
    }
    go();
    double ans=1e12;
    for(int i=0;i<200;i++) ans=min(ans,d[(n-1)*200+i]);
    printf("%.10f\n",ans);
    return 0;
} 