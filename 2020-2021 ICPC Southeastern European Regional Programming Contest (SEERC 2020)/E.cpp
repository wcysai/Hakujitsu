#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
int cnt[9];
bool valid[9][9];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            int a1=i%3,b1=i/3,a2=j%3,b2=j/3;
            a1=(a1-a2+3)%3,b1=(b1-b2+3)%3;
            if((a1*(a1-1)/2+b1*(b1-1)/2+2*a1*b1)%3==0) valid[i][j]=true; else valid[i][j]=false;
        }
    cnt[0]=1;
    int x=0,y=0;
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]%3==1) x=(x+1)%3; else if(a[i]%3==2) y=(y+1)%3;
        for(int j=0;j<9;j++) if(valid[x*3+y][j]) ans+=cnt[j];
        cnt[x*3+y]++;
    }
    printf("%lld\n",ans);
    return 0;
}