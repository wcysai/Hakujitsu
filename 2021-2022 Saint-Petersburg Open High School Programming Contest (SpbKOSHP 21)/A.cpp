#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k;
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    if(k>min(n,m)) {puts("Impossible"); return 0;}
    puts("Possible");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            if(i==j&&i<k) printf("*"); else printf(".");
        puts("");
    }
    return 0;
}