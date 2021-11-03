#include<bits/stdc++.h>
#define MAXN 55
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,x[MAXN],a[MAXN];
ll sum;
unordered_set<int> us;
int res[MAXN];
void ins(int x)
{
    if(us.count(x)) return;
    us.insert(x);
    sum+=x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&x[i],&a[i]);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        {
            if(a[i]==a[j]) continue;
            int d=x[j]-x[i];
            if(d<0) d=-d;
            for(int k=1;k*k<=d;k++)
            {
                if(d%k) continue;
                ins(k);
                if(k*k!=d) ins(d/k);
            }
        }
    for(int i=2;i<=n;i++)
    {
        if(us.count(i)) continue;
        memset(res,0,sizeof(res));
        bool f=true;
        for(int j=1;j<=n;j++)
        {
            int mod=(x[j]%i);
            if(mod<0) mod+=i;
            assert(res[mod]==0||res[mod]==a[j]);
            res[mod]=a[j];
        }
        for(int j=0;j<i;j++) if(res[j]==0) f=false;
        if(f)
        {
            f=false;
            for(int k=1;k<i;k++)
            {
                if(i%k) continue;
                bool flag=true;
                for(int l=k;l<i;l++) if(res[l]!=res[l-k]) flag=false;
                if(flag) f=true;
            }
        }
        if(f) ins(i);
    }
    printf("%d %lld\n",(int)us.size(),sum);
    return 0;
}