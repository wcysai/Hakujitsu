#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,m,k,a[MAXN],b[MAXN];
vector<int> dis;
int bit[MAXN];
int sum(int i)
{
    int s=0;
    while(i)
    {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(int i,int x)
{
    while(i<=n)
    {
        bit[i]+=x;
        i+=i&-i;
    }
}
int get_inv(vector<int> &v)
{
    int s=0;
    for(int i=(int)v.size()-1;i>=0;i--)
    {
        if(sum(v[i])&1) s^=1;
        add(v[i],1);
    }
    for(int i=0;i<(int)v.size();i++) add(v[i],-1);
    return s;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        dis.clear();
        scanf("%d",&n);
        for(int i=1;i<=n;i++) 
        {
            scanf("%d",&a[i]);
            dis.push_back(a[i]);
        }
        scanf("%d",&m);
        for(int i=1;i<=m;i++) 
        {
            scanf("%d",&b[i]);
            dis.push_back(b[i]);
        }
        scanf("%d",&k);
        if(n!=m)
        {
            puts("NIE");
            continue;
        }
        sort(dis.begin(),dis.end());
        dis.erase(unique(dis.begin(),dis.end()),dis.end());
        for(int i=1;i<=n;i++) a[i]=lower_bound(dis.begin(),dis.end(),a[i])-dis.begin()+1;
        for(int i=1;i<=m;i++) b[i]=lower_bound(dis.begin(),dis.end(),b[i])-dis.begin()+1;
        bool f=true;
        int cnt=0,same=0;
        for(int i=1;i<=k;i++)
        {
            map<int,int> mp1,mp2;
            vector<int> v1,v2;
            mp1.clear(); mp2.clear();
            for(int j=i;j<=n;j+=k)
            {
                mp1[a[j]]++; mp2[b[j]]++;
                v1.push_back(a[j]); v2.push_back(b[j]);
            }
            bool flag=false;
            for(auto p:mp1) 
            {
                if(mp2[p.F]!=p.S) {f=false; break;}
                if(p.S>1) flag=true;  
            }
            if(!flag)
            {
                if(get_inv(v1)!=get_inv(v2)) cnt++;
            }
            else same++;
            if(!f) break;
        }
        if(cnt!=0&&cnt!=k-same) f=false;
        if(f) puts("TAK"); else puts("NIE");
    }
    return 0;
}