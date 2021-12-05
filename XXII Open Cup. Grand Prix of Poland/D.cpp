#include<bits/stdc++.h>
#define MAXN 15
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m,q,dx,dy;
string str[MAXN];
string op;
vector<P> positions;
bool check(int dx,int dy)
{
    for(auto p:positions)
        if(p.F+dx>=0&&p.F+dx<n&&p.S+dy>=0&&p.S+dy<m&&str[p.F+dx][p.S+dy]=='A') return false;
    return true;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&q);
        for(int i=0;i<n;i++) cin>>str[i];
        cin>>op;
        positions.clear();
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(str[i][j]=='B') positions.push_back(P(i,j));
        dx=0,dy=0;
        for(int i=0;i<q;i++)
        {
            if(op[i]=='W')
            {
                while(dx>-10&&dx<10&&dy>-10&&dy<10&&check(dx,dy-1)) dy--;
            }
            else if(op[i]=='E')
            {
                while(dx>-10&&dx<10&&dy>-10&&dy<10&&check(dx,dy+1)) dy++;
            }
            else if(op[i]=='N')
            {
                while(dx>-10&&dx<10&&dy>-10&&dy<10&&check(dx-1,dy)) dx--;
            }
            else
            {
                while(dx>-10&&dx<10&&dy>-10&&dy<10&&check(dx+1,dy)) dx++;
            }
            if(dx<=-10||dx>=10||dy<=-10||dy>=10) break;
        }
        if(dx<=-10||dx>=10||dy<=-10||dy>=10) puts("TAK"); else puts("NIE");
    }
    return 0;
}