#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int MOD[2]={993244853,998244353};
int n,l;
string str[MAXN];
bool used[26];
map<P,int> mp;
int tot;
int get_id(P p)
{
    if(!mp.count(p)) mp[p]=++tot;
    return mp[p];
}
bool solve(vector<int> v)
{
    if(v.size()<=1) return true;
    int ch=-1;
    for(int i=0;i<26;i++)
    {
        if(used[i]) continue;
        int cnt=0;
        for(auto x:v)
        {
            for(int j=0;j<l;j++) if(str[x][j]=='a'+i) {cnt++; break;}
        }
        if(cnt==(int)v.size()) {ch=i; break;}
    }
    if(ch==-1) return false;
    vector<vector<int> > part;
    mp.clear(); tot=0;
    for(auto x:v)
    {
        P p=P(0,0);
        for(int j=0;j<l;j++)
        {
            p.F=(2*p.F+(str[x][j]=='a'+ch?1:0)); if(p.F>=MOD[0]) p.F-=MOD[0];
            p.S=(2*p.S+(str[x][j]=='a'+ch?1:0)); if(p.S>=MOD[1]) p.S-=MOD[1];
        }
        int id=get_id(p);
        if(id>part.size())
        {
            vector<int> tmp; tmp.push_back(x);
            part.push_back(tmp);
        }
        else part[id-1].push_back(x);
    }
    used[ch]=true;
    bool f=true;
    for(auto vv:part)
    {
        if(!solve(vv))
        {
            f=false;
            break;
        }
    }
    used[ch]=false;
    return f;
}
int main()
{
    scanf("%d%d",&l,&n);
    for(int i=0;i<n;i++) cin>>str[i];
    vector<int> v;
    for(int i=0;i<n;i++) v.push_back(i);
    if(solve(v)) puts("YES"); else puts("NO");
    return 0;
}