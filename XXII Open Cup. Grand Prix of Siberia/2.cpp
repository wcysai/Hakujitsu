#include<bits/stdc++.h>
#define MAXN 105
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
void dijkstra()
{
    priority_queue<PP,vector<PP>,greater<PP> > que;
    fill(d,d+100*n,1e12);
    for(int i=0;i<100;i++) d[i]=0,que.push(make_pair(0,i));
    while(!que.empty())
    {
        PP p=que.top(); que.pop();
        int v=p.second;
        if(d[v]<p.first) continue;
        for(int i=0;i<(int)G[v].size();i++)
        {
            pair<int,double> e=G[v][i];
            if(d[e.F]>d[v]+e.S)
            {
                d[e.F]=d[v]+e.S;
                que.push(P(d[e.F],e.F));
            }
        }
    }
}
double get_dist(P x,P y)
{
    return sqrt((x.F-y.F)*(x.F-y.F)+(x.S-y.S)*(x.S-y.S));
}
int main()
{
    scanf("%d%d",&n,&r);
    for(int i=0;i<n;i++) scanf("%d%d",&x[i],&y[i]);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<100;j++)
        {
            double dx=x[i]+1.0*r*cos(2*PI/100*j);
            double dy=y[i]+1.0*r*cos(2*PI/100*j);
            points[i].push_back(P(dx,dy));
        }
    }
    for(int i=0;i<n-1;i++)
        for(int j=0;j<100;j++)
            for(int k=0;k<100;k++)
                G[i*100+j].push_back(make_pair((i+1)*100+k,get_dist(points[i][j],points[i+1][k])));
    dijkstra();
    double ans=1e12;
    for(int i=0;i<100;i++) ans=min(ans,d[(n-1)*100+i]);
    printf("%.10f\n",ans);
    return 0;
} 