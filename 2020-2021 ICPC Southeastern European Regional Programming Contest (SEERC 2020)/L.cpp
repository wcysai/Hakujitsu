#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
P p[MAXN];
ll v[MAXN];
bool cmp(P x,P y)
{
    //x.F-y.S>y.F-x.S
    return x.F+x.S>y.F+y.S;
}
bool check(int x)
{
    //printf("x=%d\n",x);
    priority_queue<int,vector<int>,greater<int> > pq1;
    ll sum=0;
    for(int i=1;i<=x;i++) pq1.push(p[i].F),sum+=p[i].F;
    v[x]=sum;
    for(int i=x+1;i<=n-x;i++)
    {
        pq1.push(p[i].F); sum+=p[i].F;
        sum-=pq1.top(); pq1.pop();
        v[i]=sum;
        //printf("i=%d sum=%lld\n",i,sum);
    }
    sum=0;
    priority_queue<int> pq2;
    for(int i=n;i>=n-x+1;i--) pq2.push(p[i].S),sum+=p[i].S;
    v[n-x]-=sum; if(v[n-x]>=0) return true;
    for(int i=n-x;i>=x+1;i--)
    {
        pq2.push(p[i].S); sum+=p[i].S;
        sum-=pq2.top(); pq2.pop();
        //printf("i=%d sum=%lld\n",i,sum);
        v[i-1]-=sum; if(v[i-1]>=0) return true;
    }
    return false;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&p[i].F);
    for(int i=1;i<=n;i++) scanf("%d",&p[i].S);
    sort(p+1,p+n+1,cmp);
    //for(int i=1;i<=n;i++) printf("%d %d\n",p[i].F,p[i].S);
    int l=0,r=n/2+1;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(check(mid)) l=mid; else r=mid;
    }
    printf("%d\n",l);
    return 0;
}