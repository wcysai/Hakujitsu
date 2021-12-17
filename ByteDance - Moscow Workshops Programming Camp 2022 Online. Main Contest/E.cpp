#include<bits/stdc++.h>
#define MAXN 150005
#define MAXM 405
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
vector<char> str[MAXM];
int timestamp[MAXN];
int to[MAXN];
vector<int> rG[MAXN];
string tmp;
int nl,nr,ml,mr;
vector<pair<P,P> > restrictions;
vector<pair<P,int> > v[MAXM];
vector<int> mini[MAXM];
char trans(char &ch)
{
    if(ch=='>') return 'v';
    else if(ch=='v') return '>';
    else if(ch=='^') return '<';
    else return '^';
}
void upd(int id)
{
    nl=min(nl,id/m); nr=max(nr,id/m); ml=min(ml,id%m); mr=max(mr,id%m);
}
void solve(int i,int j)
{
    int id=i*m+j;
    int tot=0;
    vector<int> path; 
    while(id!=n*m&&!timestamp[id])
    {
        timestamp[id]=++tot;
        path.push_back(id);
        id=to[id];
    }
    queue<int> que;
    if(id!=n*m)
    {
        int len=(tot+1)-timestamp[id];
        nl=n+1; ml=m+1; nr=-1; mr=-1;
        for(int j=0;j<len;j++)
        {
            int nid=path.back(); path.pop_back(); timestamp[nid]=-1;
            que.push(nid);
            upd(nid);
        }
        restrictions.push_back(make_pair(P(nl,nr),P(ml,mr)));
    }
    else que.push(path.back());
    while(que.size())
    {
        int v=que.front(); que.pop();
        for(auto to:rG[v]) 
        {
            if(timestamp[to]!=-1)
            {
                que.push(to);
                timestamp[to]=-1;
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    bool swapped=false;
    if(n>m) {swapped=true; for(int i=0;i<m;i++) str[i].resize(n);}
    else {for(int i=0;i<n;i++) str[i].resize(m);}
    for(int i=0;i<n;i++) 
    {
        cin>>tmp;
        if(swapped)
        {
            for(int j=0;j<m;j++) 
                str[j][i]=trans(tmp[j]);
        }
        else 
        {
            for(int j=0;j<m;j++) str[i][j]=tmp[j];
        }
    }
    if(swapped) swap(n,m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            int x=i,y=j,nxt;
            if(str[i][j]=='<') y--; else if(str[i][j]=='>') y++; else if(str[i][j]=='v') x++; else x--;
            if(x>=0&&x<n&&y>=0&&y<m) nxt=x*m+y; else nxt=n*m;
            to[i*m+j]=nxt;
            if(nxt!=n*m) rG[nxt].push_back(i*m+j);
        }
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(!timestamp[i*m+j]) solve(i,j);
    for(auto p:restrictions)
        for(int i=p.F.S;i<=n-1;i++)
            v[i].push_back(make_pair(P(p.F.F,p.S.F),p.S.S));
    int ans=-1;
    int xl=-1,xr=-1,yl=-1,yr=-1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++) 
        {
            mini[j].clear(),mini[j].resize(m);
            for(int k=0;k<m;k++) mini[j][k]=m-1;
        }
        for(auto p:v[i]) mini[p.F.F][p.F.S]=min(mini[p.F.F][p.F.S],p.S-1);
        for(int j=n-1;j>=0;j--)
            for(int k=m-1;k>=0;k--)
            {
                if(j!=n-1) mini[j][k]=min(mini[j][k],mini[j+1][k]);
                if(k!=m-1) mini[j][k]=min(mini[j][k],mini[j][k+1]);
            }
        for(int j=0;j<=i;j++)
            for(int k=0;k<m;k++)
            {
                if((i-j+1)*(mini[j][k]-k+1)>ans)
                {
                    ans=(i-j+1)*(mini[j][k]-k+1);
                    xl=j; xr=i; yl=k; yr=mini[j][k];
                }
            }
    }
    assert(ans!=-1);
    if(swapped) printf("%d %d %d %d\n",yl+1,xl+1,yr+1,xr+1); else printf("%d %d %d %d\n",xl+1,yl+1,xr+1,yr+1);
    return 0;
}