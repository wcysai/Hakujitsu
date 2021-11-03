#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,p[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&p[i]);
    int k=1;
    for(int i=1;i<=n;i++)
        if(p[i]>i) k=max(k,p[i]-i+1);
    printf("%d\n",k);
    return 0;
}