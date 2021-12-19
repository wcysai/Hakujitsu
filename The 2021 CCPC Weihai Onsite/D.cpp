#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int MOD[2]={998244353,993244853};
int BASE[2]={19260817,19990303};
int pw[2][MAXN];
P pre[MAXN],suf[MAXN];
int sum[MAXN];
int n,q;
char str[MAXN];
int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    pre[0]=P(0,0); suf[n+1]=P(0,0);
    for(int i=0;i<2;i++)
    {
        pw[i][0]=1;
        for(int j=1;j<=n;j++) pw[i][j]=1LL*pw[i][j-1]*BASE[i]%MOD[i];
    }
    for(int i=1;i<=n;i++)
    {
        pre[i].F=(1LL*pre[i-1].F*BASE[0]+(str[i]-'a'+1))%MOD[0];
        pre[i].S=(1LL*pre[i-1].S*BASE[1]+(str[i]-'a'+1))%MOD[1];
        //printf("pre:(%d %d %d)\n",i,pre[i].F,pre[i].S);
    }
    for(int i=n;i>=1;i--)
    {
        suf[i].F=(1LL*(str[i]-'a'+1)*pw[0][n-i]+suf[i+1].F)%MOD[0];
        suf[i].S=(1LL*(str[i]-'a'+1)*pw[1][n-i]+suf[i+1].S)%MOD[1];
        //printf("suf:(%d %d %d)\n",i,suf[i].F,suf[i].S);
    }
    for(int i=1;i<=n;i++) if(pre[i]==suf[n-i+1]) sum[i]=sum[i-1]+1; else sum[i]=sum[i-1];
    scanf("%d",&q);
    while(q--)
    {
        int x;
        scanf("%d",&x);
        int len=min(x-1,n-x);
        printf("%d\n",sum[len]);
    }
    return 0;
}