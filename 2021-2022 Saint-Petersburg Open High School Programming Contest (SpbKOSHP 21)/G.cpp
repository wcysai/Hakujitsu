#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,ll> P;
typedef bitset<100000> bs;
int n;
ll a[MAXN],b[MAXN],bas[62];
bs res[62];
bool good[61];
void add_basis(ll x,int id)
{
    vector<int> tmp; 
    int save=-1; 
    for(int j=60;j>=0;j--)
    {
        if(x&(1LL<<j))
        {
            if(!bas[j])
            { 
                bas[j]=x; save=j; 
                break;
            }
            x^=bas[j]; tmp.push_back(j);
        }
    }
    if(save!=-1)
    {
        bs b; b.set(id-1);
        for(auto x:tmp) b^=res[x];
        res[save]=b;
    }
}
int main()
{
    scanf("%d",&n);
    ll x=0;
    for(int i=1;i<=n;i++) 
    {
        scanf("%lld",&a[i]); 
        x^=a[i]; 
    }
    ll s=x;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&b[i]);
        s^=b[i];
    }
    ll mask=0;
    for(int i=0;i<=60;i++) if(s&(1LL<<i)) good[i]=false; else {good[i]=true; mask^=(1LL<<i);}
    printf("mask=%lld\n",mask);
    for(int i=1;i<=n;i++)
    {
        ll tmp=(a[i]^b[i])&mask;
        add_basis(tmp,i);
    }
    ll cur=(x&mask);
    bs b;
    for(int i=60;i>=0;i--)
    {
        if(!good[i]) continue;
        if((!(cur&(1LL<<i)))&&bas[i]) {cur^=bas[i]; b^=res[i];}
    }
    printf("%lld %d\n",cur+(s^cur),b.count());
    for(int i=0;i<n;i++) if(b.test(i)) printf("%d ",i+1);
    return 0;
}