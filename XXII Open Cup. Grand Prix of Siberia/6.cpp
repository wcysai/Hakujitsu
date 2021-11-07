#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m;
int a[MAXN][MAXN],bas[MAXN][MAXN];
int inv[7]={0,1,4,5,2,3,6};
map<string,int> mp;
string str[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
string s[MAXN];
int cnt;
void ins(int x)
{
    int tmp[MAXN];
    for(int i=1;i<=m;i++) tmp[i]=a[x][i];
    for(int i=1;i<=m;i++)
    {
        if(tmp[i])
        {
            if(!bas[i][i])
            {
                cnt++;
                for(int k=1;k<=m;k++) bas[i][k]=tmp[k];
                break;
            }
            int mult=tmp[i]*inv[bas[i][i]]%7;
            for(int k=1;k<=m;k++) 
            {
                tmp[k]=(tmp[k]-mult*bas[i][k])%7;
                if(tmp[k]<0) tmp[k]+=7;
            }
        }
    }
}
string get_next(string &ss)
{
    int id=mp[ss];
    id=(id+1)%7;
    return str[id];
}
int main()
{
    for(int i=0;i<=6;i++) mp[str[i]]=i;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++) cin>>s[i];
        for(int i=1;i<=n;i++)
        {
            memset(a[i],0,sizeof(a[i]));
            int k; scanf("%d",&k);
            for(int j=0;j<k;j++)
            {
                int x;
                scanf("%d",&x);
                a[i][x]=1;
            }
        }
        cnt=0;
        for(int i=1;i<=m;i++) memset(bas[i],0,sizeof(bas[i]));
        for(int i=1;i<=n;i++) ins(i);
        if(cnt==m) puts("NO"); else 
        {
            printf("YES");
            int id=-1;
            for(int i=1;i<=m;i++) if(!bas[i][i]) {id=i; break;}
            s[id]=get_next(s[id]);
            for(int i=1;i<=m;i++) cout<<" "<<s[i];
            puts("");
        }
    }
    return 0;
}