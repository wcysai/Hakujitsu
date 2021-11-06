#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,t[MAXN],d[MAXN];
int dir,et;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&t[i],&d[i]);
    dir=-1;
    bool oppo=false;
    for(int i=1;i<=n;i++)
    {
        if(dir==-1)
        {
            dir=d[i];
            et=t[i]+10;
            continue;
        }
        if(t[i]>=et&&oppo)
        {
            oppo=false;
            dir=1-dir;
            et=et+10;
        }
        if(t[i]>=et)
        {
            dir=d[i];
            et=t[i]+10;
        }
        else if(dir==d[i]) et=t[i]+10;
        else
        {
            oppo=true;
        }
    }
    if(oppo) et+=10;
    printf("%d\n",et);
    return 0;
}