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
ll sum[MAXN];
bool valid[MAXN];
set<P> blocked;
ll ask(int l,int r)
{
    printf("? %d %d\n",l,r);
    fflush(stdout);
    ll x; int y,z; scanf("%lld%d%d",&x,&y,&z);
    blocked.insert(P(y,z));
    return x;
}
void answer()
{
    printf("!\n"); 
    for(int i=1;i<=n;i++) printf("%lld ",sum[i]-sum[i-1]);
    printf("\n");
    fflush(stdout);
}
int main()
{
    scanf("%d",&n);
    memset(valid,false,sizeof(valid));
    valid[0]=true; sum[0]=0;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=i-1;j++)
            if(!blocked.count(P(j+1,i)))
            {
                sum[i]=ask(j+1,i)+sum[j];
                break;
            }
    answer();
    return 0;
}