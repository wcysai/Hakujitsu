#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,s,n,f,m;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d",&s,&n,&f,&m);
        int maxi=n*f+m,mini=n+m;
        if(s>=mini&&s<=maxi) puts("YES"); else puts("NO");
    }
    return 0;
}