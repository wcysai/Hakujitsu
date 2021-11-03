#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
mt19937 wcy(time(NULL));
int main()
{
    freopen("B.in","w",stdout);
    printf("%d\n",200000);
    for(int i=0;i<200000;i++) printf("%c",'a'+wcy()%26);
    printf("\n");
    return 0;
}