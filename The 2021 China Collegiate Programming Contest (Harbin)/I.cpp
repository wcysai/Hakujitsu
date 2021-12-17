#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,a[MAXN];
int b[31];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        memset(b,0,sizeof(b));
        for(int i=1;i<=n;i++) 
        {
            scanf("%d",&a[i]);
            for(int j=0;j<=30;j++) if(a[i]&(1<<j)) b[j]++;
        }
        for(int iter=0;;iter++)
        {
            bool update=false;
            for(int i=30;i>=1;i--)
            {
                if(b[i]>b[i-1])
                {
                    update=true;
                    int dif=b[i]-b[i-1];
                    int need=(dif+2)/3;
                    b[i]-=need; b[i-1]+=need*2;
                }
            }
            if(!update) break;
        }
        printf("%d\n",b[0]);
    }
    return 0;
}