#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int q,t[MAXN],x[MAXN];
vector<int> G[MAXN];
int fa[MAXN];
int cnt[MAXN],id,cur;
bool dead[MAXN];
void go()
{
    while(dead[cur])
    {
        if(G[cur].size()==cnt[cur]) cur=fa[cur];
        else
        {
            cnt[cur]++;
            cur=G[cur][cnt[cur]-1];
        }
    }
}
int main()
{
    scanf("%d",&q);
    memset(dead,false,sizeof(dead));
    id=1; cur=1;
    for(int i=0;i<q;i++)
    {
        scanf("%d%d",&t[i],&x[i]);
        if(t[i]==1)
        {
            id++;
            G[x[i]].push_back(id);
            fa[id]=x[i];
        }
        else
        {
            dead[x[i]]=true;
            if(dead[cur]) go(); 
            printf("%d\n",cur);
        }
    }
    return 0;
}