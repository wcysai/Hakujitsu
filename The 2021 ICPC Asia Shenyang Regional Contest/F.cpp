#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
string str;
int mp[26];
string encode(string &str)
{
    int sz=(int)str.size();
    memset(mp,-1,sizeof(mp));
    int cnt=0;
    for(int i=sz-1;i>=0;i--)
    {
        if(mp[str[i]-'a']==-1)
        {
            mp[str[i]-'a']=cnt;
            cnt++;
        }
    }
    string tmp="";
    for(int i=0;i<sz;i++) tmp+=(char)('a'+mp[str[i]-'a']);
    return tmp;
}
int main()
{
    scanf("%d",&n);
    cin>>str;
    string ans="";
    for(int i=0;i<n;i++)
    {
        string tmp=encode(str);
        if(tmp>ans) ans=tmp;
        str.pop_back();
    }
    cout<<ans<<endl;
    return 0;
}