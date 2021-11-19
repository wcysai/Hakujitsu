#include<bits/stdc++.h>
#define MAXN 10000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int ans,pw[MAXN],par[MAXN];
bool vis[MAXN];
vector<int> trans[MAXN],id;
int n,k;
vector<int> composition(vector<int> &p,vector<int> &q)
{
    vector<int> ret(n);
    for(int i=0;i<n;i++) ret[i]=q[p[i]];
    return ret;
}
int compute_hash(vector<int> v)
{
    int res=0;
    for(int i=0;i<n;i++) res+=v[i]*pw[i];
    return res;
}
vector<int> find_perm(int hsh)
{
    vector<int> p(n);
    for(int i=0;i<=n-1;i++) p[i]=(hsh%pw[i+1])/pw[i];
    return p;
}
void init()
{
    id.resize(n);
    for(int i=0;i<n;i++) id[i]=i;
    for(int i=0;i+k<n;i++)
    {
        trans[i].resize(n);
        for(int j=0;j<i;j++) trans[i][j]=id[j];
        trans[i][i+k]=id[i];
        for(int j=i;j<i+k;j++) trans[i][j]=id[j+1];
        for(int j=i+k+1;j<n;j++) trans[i][j]=j;
        printf("i=%d\n",i);
        for(auto x:trans[i]) printf("%d ",x);
        puts("");
    }
    int tot=n-k;
    for(int i=n-1;i>=k;i--)
    {
        trans[tot].resize(n);
        for(int j=i+1;j<n;j++) trans[tot][j]=id[j];
        trans[tot][i-k]=id[i];
        for(int j=i;j>i-k;j--) trans[tot][j]=id[j-1];
        for(int j=i-k-1;j>=0;j--) trans[tot][j]=id[j];
        printf("tot=%d\n",tot);
        for(auto x:trans[tot]) printf("%d ",x);
        puts("");
        tot++;
    }
}
void bfs()
{
    ans=1;
    memset(vis,false,sizeof(vis));
    int st=compute_hash(id); vis[st]=true;
    queue<int> que; que.push(st);
    while(que.size())
    {
        int hsh=que.front(); que.pop();
        vector<int> tmp=find_perm(hsh); 
        for(int i=0;i<2*(n-k);i++)
        {
            int nxt=compute_hash(composition(trans[i],tmp));
            if(!vis[nxt])
            {
                vis[nxt]=true;
                par[nxt]=hsh;
                ans++;
                que.push(nxt);
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    pw[0]=1;
    for(int i=1;i<=n;i++) pw[i]=pw[i-1]*n;
    init();
    bfs();
    printf("%d\n",ans);
    while(1){
        vector<int> paa(n);
        for (int i=0;i<n;++i) scanf("%d",&paa[i]);
        int hsh=compute_hash(paa);
        while (hsh){
            auto ret=find_perm(hsh);
            for (auto c:ret) cout<<c<<" ";
            cout<<"\n";
            hsh=par[hsh];
        }
    }
    return 0;
}