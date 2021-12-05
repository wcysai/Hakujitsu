#include<bits/stdc++.h>
#define MAXN 30005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
int T,n,k,a[MAXN];
vector<int> id;
int solve2(vector<int> &l,vector<int> &r,int b)
{
    if(!l.size()) return (int)r.size();
    if(!r.size()) return (int)l.size();
    /*printf("b=%d ",b);
    for(auto x:l) printf("%d ",a[x]);
    puts("");
    for(auto x:r) printf("%d ",a[x]);
    puts("");*/
    if(b<0) return (int)l.size()+(int)r.size();
    vector<int> lzero,lone,rzero,rone;
    for(auto x:l) if(a[x]&(1<<b)) lone.push_back(x); else lzero.push_back(x);
    for(auto x:r) if(a[x]&(1<<b)) rone.push_back(x); else rzero.push_back(x);
    if(k&(1<<b))
    {
        return solve2(lzero,rone,b-1)+solve2(lone,rzero,b-1);
    }
    else
    {
        return max(max((int)l.size(),(int)r.size()),max(solve2(lzero,rzero,b-1),solve2(lone,rone,b-1)));
    }
}
int solve(vector<int> &id,int b)
{
    if(!id.size()) return 0;
    if(b<0) return (int)id.size();
    vector<int> zero,one;
    for(auto x:id) if(a[x]&(1<<b)) one.push_back(x); else zero.push_back(x);
    if(k&(1<<b))
    {
        int res=max((int)one.size(),(int)zero.size());
        return max(res,solve2(zero,one,b-1));
    }
    else
    {
        return max(solve(zero,b-1),solve(one,b-1));
    }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        id.clear();
        for(int i=1;i<=n;i++) id.push_back(i);
        printf("%d\n",solve(id,19));
    }
    return 0;
}