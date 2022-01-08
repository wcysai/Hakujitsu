#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    int s=0;
    for(int i=(n+1)/2+1;i<=n;i++) s+=a[i];
    printf("%d\n",s);
    return 0;
}