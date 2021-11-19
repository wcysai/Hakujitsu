#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a,b,x[MAXN],y[MAXN];
int type[MAXN];
int main()
{
    scanf("%d%d%d",&n,&a,&b);
    ll sum=0;
    priority_queue<P> pque;
    for(int i=1;i<=n;i++) {scanf("%d",&x[i]); sum+=x[i];}
    for(int i=1;i<=n;i++) {scanf("%d",&y[i]); pque.push(P(y[i]-x[i],i));}
    memset(type,0,sizeof(type));
    for(int i=0;i<b;i++)
    {
        P p=pque.top(); pque.pop();
        sum+=p.F; type[p.S]=1;
    }
    int left=n-b;
    while(pque.size()&&pque.top().F>0) 
    {
        if(left==a) break;
        P p=pque.top(); pque.pop();
        sum+=p.F; type[p.S]=1;
        left--;
    }
    printf("%lld\n",sum);
    for(int i=1;i<=n;i++) if(type[i]) printf("P "); else printf("T ");
    return 0;
}