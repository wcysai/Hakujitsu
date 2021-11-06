#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,K;
int n[MAXN],c[MAXN],a[MAXN];
vector<int> val[MAXN];
int main()
{
    scanf("%d%d",&N,&K);
    for(int i=1;i<=N;i++)
    {
        scanf("%d%d",&n[i],&c[i]);
        val[c[i]].push_back(n[i]);
    }
    for(int i=1;i<=K;i++) sort(val[i].begin(),val[i].end(),greater<int>());
    for(int i=1;i<=N;i++)
    {
        a[i]=val[c[i]].back();
        val[c[i]].pop_back();
        if(a[i]!=i) {puts("N"); return 0;}
    }
    puts("Y");
    return 0;
}