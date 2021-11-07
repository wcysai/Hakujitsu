#include<bits/stdc++.h>
#define MAXN 36005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int cnt[6][6];
queue<int> minor[2],major[2];
int q;
int parse(string &str)
{
    return (str[0]-'0')*6000+(str[1]-'0')*600+(str[3]-'0')*100+(str[4]-'0')*10+(str[6]-'0');
}
string get_str(int tt)
{
    string str="";
    str+=(tt/6000)+'0'; tt%=6000;
    str+=(tt/600)+'0'; tt%=600;
    str+=':';
    str+=(tt/100)+'0'; tt%=100;
    str+=(tt/10)+'0'; tt%=10;
    str+='.';
    str+=tt+'0';
    return str;
}
vector<pair<int,string> > events[MAXN];
int main()
{
    scanf("%d",&q);
    int last=0,a[2]={5,5};
    for(int i=0;i<q;i++)
    {
        string str;
        cin>>str;
        int tt=parse(str);
        int pos;
        scanf("%d",&pos); pos--;
        cin>>str;
        events[tt].push_back(make_pair(pos,str));
    }
    for(int i=0;i<36000;i++)
    {
        for(int j=0;j<2;j++)
        {
            while(minor[j].size()&&minor[j].front()<=i-1200) minor[j].pop(),a[j]++;
            while(major[j].size()&&major[j].front()<=i-3000) major[j].pop(),a[j]++;
        }
        for(auto p:events[i])
        {
            if(p.S=="minor") minor[p.F].push(i),a[p.F]--;
            else if(p.S=="major") major[p.F].push(i),a[p.F]--;
            else
            {
                if(a[1-p.F]<a[p.F]&&minor[1-p.F].size()) minor[1-p.F].pop(),a[1-p.F]++;
            }
        }
        //printf("%d %d %d\n",i,a[0],a[1]);
        cnt[a[0]][a[1]]++;
    }
    for(int i=0;i<=5;i++)
        for(int j=0;j<=5;j++)
            if(cnt[i][j]) {printf("%dx%d ",i,j); cout<<get_str(cnt[i][j])<<endl;}
    return 0;
}