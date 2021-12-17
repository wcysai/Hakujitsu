#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,a[MAXN][MAXN],row[MAXN],col[MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) row[i]=INF;
    for(int i=1;i<=m;i++) col[i]=INF;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
            row[i]=min(row[i],a[i][j]); col[j]=min(col[j],a[i][j]);
        }
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(row[i]==a[i][j]&&col[j]==a[i][j]) ans++;
    printf("%d\n",ans);
    return 0;
}