#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 500005
#define MAXM 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
mt19937 wcy(time(NULL));
int n;
int main()
{
    freopen("A.in","w",stdout);
    n=100000;
    printf("%d\n",n);
    for(int i=2;i<=n;i++)
        printf("%d %d\n",wcy()%(i-1)+1,i);
    for(int i=2;i<=n;i++)
        printf("%d %d\n",wcy()%(i-1)+1,i);
}