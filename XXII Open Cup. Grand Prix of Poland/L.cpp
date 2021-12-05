#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m,k;
string str[MAXN];
int d[MAXN][MAXN];
queue<P> que;
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
void init()
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            d[i][j]=INF;
}
void bfs()
{
    while(que.size())
    {
        P p=que.front(); que.pop();
        int x=p.F,y=p.S;
        if(d[x][y]>=k) continue;
        for(int dir=0;dir<4;dir++)
        {
            int nx=x+dx[dir],ny=y+dy[dir];
            if(nx>=0&&nx<n&&ny>=0&&ny<m&&d[nx][ny]==INF)
            {
                d[nx][ny]=d[x][y]+1;
                que.push(P(nx,ny));
            } 
        }
    }
}

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=0;i<n;i++) cin>>str[i];
        init();
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(str[i][j]=='.') {d[i][j]=0; que.push(P(i,j));}
        bfs();
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(d[i][j]>k) {d[i][j]=0; que.push(P(i,j));} else d[i][j]=INF;
        bfs();
        bool f=true;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(str[i][j]=='x'&&d[i][j]>k) f=false;
        if(f) puts("TAK"); else puts("NIE"); 
    }
    return 0;
}