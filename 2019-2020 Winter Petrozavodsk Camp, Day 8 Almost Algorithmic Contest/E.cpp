#include<bits/stdc++.h>
#define MAXN 8005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,x;
int mini[8*MAXN];
int rk[MAXN];
int getmin(int x,int y)
{
    if(x==0) return y;
    else if(y==0) return x;
    return rk[x]<rk[y]?x:y;
}
string str;
int main()
{
    scanf("%d",&n);
    int k=1;
    while(k<=n) k*=2;
    memset(mini,0,sizeof(mini));
    for(int i=0;i<n*2;i++)
    {
        cin>>str; scanf("%d",&x);
        if(str=="add")
        {
            mini[k+x-1]=x;
            vector<int> v;
            int now=k+x-1;
            while(now>1)
            {
                if(mini[now]) v.push_back(mini[now]);
                if(mini[now^1]) v.push_back(mini[now^1]);
                now/=2;
            }
            sort(v.begin(),v.end());
            v.erase(unique(v.begin(),v.end()),v.end());
            int sz=(int)v.size();
            printf("%d",(int)sz);
            for(auto x:v) printf(" %d",x);
            printf("\n");
            fflush(stdout);
            for(int j=0;j<sz;j++) 
            {
                int y;
                scanf("%d",&y);
                rk[y]=j;
            }
            now=k+x-1;
            while(now>1)
            {
                now/=2;
                mini[now]=getmin(mini[now*2],mini[now*2+1]);
            }
        }
        else
        {
            mini[k+x-1]=0;
            vector<int> v;
            int now=k+x-1;
            while(now>1)
            {
                if(mini[now]&&mini[now]!=x) v.push_back(mini[now]);
                if(mini[now^1]&&mini[now^1]!=x) v.push_back(mini[now^1]);
                now/=2;
            }
            sort(v.begin(),v.end());
            v.erase(unique(v.begin(),v.end()),v.end());
            int sz=(int)v.size();
            printf("%d",(int)sz);
            for(auto x:v) printf(" %d",x);
            printf("\n");
            fflush(stdout);
            for(int j=0;j<sz;j++) 
            {
                int y;
                scanf("%d",&y);
                rk[y]=j;
            }
            now=k+x-1;
            while(now>1)
            {
                now/=2;
                mini[now]=getmin(mini[now*2],mini[now*2+1]);
            }
        }
        if(mini[1]==0) printf("-1\n"); else printf("%d\n",mini[1]);
        fflush(stdout);
    }
    return 0;
}