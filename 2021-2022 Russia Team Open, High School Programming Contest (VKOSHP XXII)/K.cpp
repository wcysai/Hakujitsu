#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
vector<int> v[2];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) 
    {
        v[0].push_back(a[i]);
        printf("%d\n",1);
    }
    int cur=0;
    for(int i=1;i<=n;i++)
    {
        while(v[cur].back()!=i) 
        {
            v[cur^1].push_back(v[cur].back());
            v[cur].pop_back();
            printf("%d%d\n",cur+1,(cur^1)+1);
        }
        printf("-%d\n",cur+1); v[cur].pop_back();
        while(v[cur].size()) 
        {
            v[cur^1].push_back(v[cur].back());
            v[cur].pop_back();
            printf("%d%d\n",cur+1,(cur^1)+1);
        }
        cur^=1;
    }
    return 0;
}