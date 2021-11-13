#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,c,q,t,k,v[MAXN],x[MAXN],d[MAXN];
vector<int> velo;
int main()
{
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d%d%d",&v[i],&x[i],&d[i]);
        velo.push_back(v[i]);
    }
    sort(velo.begin(),velo.end());
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d%d",&t,&k);
        printf("%.10f\n",sqrt(1.0*velo[k-1]*velo[k-1]+2.0*c*t));
    }
    return 0;
}