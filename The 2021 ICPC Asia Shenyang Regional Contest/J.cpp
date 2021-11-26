#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
string s,t;
int d[MAXN];
int trans(int v,int i,int j,int k)
{
    int tmp[4];
    tmp[3]=v%10; tmp[2]=(v%100)/10; tmp[1]=(v%1000)/100; tmp[0]=v/1000;
    for(int x=i;x<=j;x++) 
    {
        if(k==0) tmp[x]++; else tmp[x]--;
        if(tmp[x]==10) tmp[x]=0;
        if(tmp[x]==-1) tmp[x]=9;
    }
    return tmp[0]*1000+tmp[1]*100+tmp[2]*10+tmp[3];
}
void bfs(int s)
{
    fill(d,d+10000,INF);
    d[s]=0;
    queue<int> que; que.push(s);
    while(que.size())
    {
        int v=que.front(); que.pop();
        for(int i=0;i<4;i++)
        {
            for(int j=i;j<4;j++) 
                for(int k=0;k<2;k++)
                {
                    int nxt=trans(v,i,j,k);
                    if(d[nxt]==INF)
                    {
                        d[nxt]=d[v]+1;
                        que.push(nxt);
                    }
                }
        }
    }
}
int main()
{
    scanf("%d",&T);
    bfs(0);
    while(T--)
    {
        cin>>s>>t;
        int tmp[4];
        for(int i=0;i<4;i++) 
        {
            tmp[i]=s[i]-t[i];
            if(tmp[i]<0) tmp[i]+=10;
            if(tmp[i]>=10) tmp[i]-=10;
        }
        int dif=tmp[0]*1000+tmp[1]*100+tmp[2]*10+tmp[3];
        printf("%d\n",d[dif]);
    }
    return 0;
}