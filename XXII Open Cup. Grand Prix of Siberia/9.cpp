#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
vector<int> a[MAXN],b[MAXN];
map<P,int> mp[MAXN];
int MOD[2]={993244853,1000000009};
int BASE[2]={233,666};
int fact[2][MAXN],mini;
int main()
{
    fact[0][0]=fact[1][0]=1;
    for(int i=0;i<2;i++)
        for(int j=1;j<=100000;j++)
            fact[i][j]=1LL*fact[i][j-1]*j%MOD[i];
    scanf("%d%d",&n,&m);
    int mini=INF;
    for(int i=0;i<n;i++)
    {
        int deg; scanf("%d",&deg);
        for(int j=0;j<=deg;j++) 
        {
            int x;
            scanf("%d",&x);
            a[i].push_back(x);
        }
        mini=min(mini,deg+1);
        P p=P(0,0);
        for(int j=deg;j>=0;j--)
        {
            int x=1LL*a[i][j]*fact[0][j]%MOD[0];
            int y=1LL*a[i][j]*fact[1][j]%MOD[1];
            p.F=(1LL*p.F*BASE[0]+x)%MOD[0]; p.S=(1LL*p.S*BASE[1]+y)%MOD[1];
            if(mp[deg-j+1].find(p)==mp[deg-j+1].end()) mp[deg-j+1][p]=deg+1; else mp[deg-j+1][p]=min(deg+1,mp[deg-j+1][p]);
        }
    }
    for(int i=0;i<m;i++)
    {
        int deg; scanf("%d",&deg);
        for(int j=0;j<=deg;j++) 
        {
            int x;
            scanf("%d",&x);
            b[i].push_back(x);
        }
        int ans=mini+deg+1;
        P p=P(0,0);
        for(int j=deg;j>=0;j--)
        {
            int x=1LL*b[i][j]*fact[0][j]%MOD[0];
            int y=1LL*b[i][j]*fact[1][j]%MOD[1];
            p.F=(1LL*p.F*BASE[0]+x)%MOD[0]; p.S=(1LL*p.S*BASE[1]+y)%MOD[1];
            if(mp[deg-j+1].find(p)!=mp[deg-j+1].end()) ans=min(ans,mp[deg-j+1][p]+deg+1-2*(deg-j+1)); 
        }
        printf("%d\n",ans);
    }
    return 0;
}