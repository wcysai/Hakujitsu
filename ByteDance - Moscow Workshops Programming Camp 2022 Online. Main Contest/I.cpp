#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
string str;
int cnt[26];
int ensure[26];
bool cmp(string &x,string &y)
{
    if(x.size()!=y.size()) return x.size()>y.size();
    return x<y;
}
int main()
{
    cin>>str;
    n=(int)str.size();
    memset(ensure,0,sizeof(ensure));
    for(int i=0;i<n;i++) cnt[str[i]-'a']++;
    int maxi=0;
    for(int i=0;i<26;i++) maxi=max(maxi,cnt[i]);
    if(maxi==1)
    {
        for(int i=0;i<26;i++)
        {
            if(cnt[i])
            {
                cout<<(char)(i+'a')<<endl;
                return 0;
            }
        }
    }
    for(int i=0;i<26;i++)
    {
        ensure[i]=(cnt[i]/4)*4;
        cnt[i]%=4;
    }
    string cur="";
    for(int i=0;i<26;i++)
        for(int j=0;j<26;j++)
        {
            if(i==j) continue;
            if(cnt[i]<3||cnt[j]<2) continue;
            string tmp="";
            tmp+=(char)('a'+i); tmp+=(char)('a'+j); tmp+=(char)('a'+i); 
            tmp+=(char)('a'+j); tmp+=(char)('a'+i);
            if(cmp(tmp,cur)) cur=tmp;
        }
    for(int i=0;i<26;i++)
    {
        if(cnt[i]<3) continue;
        string tmp="";
        tmp+=(char)('a'+i); tmp+=(char)('a'+i); tmp+=(char)('a'+i); 
        if(cmp(tmp,cur)) cur=tmp;
    }
    for(int i=0;i<26;i++)
    {
        if(cnt[i]<2) continue;
        string tmp="";
        tmp+=(char)('a'+i); tmp+=(char)('a'+i); 
        if(cmp(tmp,cur)) cur=tmp;
    }
    for(int i=0;i<26;i++)
    {
        if(cnt[i]<1||!ensure[i]) continue;
        string tmp="";
        tmp+=(char)('a'+i); 
        if(cmp(tmp,cur)) cur=tmp;
    }
    if(cur.size()==0)
    {
        string ans="";
        for(int i=0;i<26;i++) 
            for(int j=0;j<ensure[i]/4;j++) 
                ans+=(char)('a'+i);
        string tmp=ans; reverse(tmp.begin(),tmp.end()); ans+=tmp;
        ans+=ans;
        cout<<ans<<endl;
    }
    else if(cur.size()==1)
    {
        int id=(int)(cur[0]-'a');
        string tmp="",ans="",rtmp;
        ensure[id]--;
        for(int i=0;i<26;i++) 
            for(int j=0;j<ensure[i]/4;j++) 
                tmp+=(char)('a'+i);
        rtmp=tmp; reverse(rtmp.begin(),rtmp.end()); 
        ans+=cur[0]; ans+=tmp; ans+=cur[0]; ans+=rtmp; 
        ans+=cur[0]; ans+=tmp; ans+=cur[0]; ans+=rtmp; ans+=cur[0];
        cout<<ans<<endl;
    }
    else if(cur.size()==2)
    {
        string tmp="",ans="",rtmp;
        for(int i=0;i<26;i++) 
            for(int j=0;j<ensure[i]/4;j++) 
                tmp+=(char)('a'+i);
        rtmp=tmp; reverse(rtmp.begin(),rtmp.end()); 
        ans+=tmp; ans+=cur[0]; ans+=rtmp; 
        ans+=tmp; ans+=cur[0]; ans+=rtmp; 
        cout<<ans<<endl;
    }
    else if(cur.size()==3)
    {
        string tmp="",ans="",rtmp;
        for(int i=0;i<26;i++) 
            for(int j=0;j<ensure[i]/4;j++) 
                tmp+=(char)('a'+i);
        rtmp=tmp; reverse(rtmp.begin(),rtmp.end()); 
        ans+=cur[0]; ans+=tmp;  ans+=rtmp;  ans+=cur[0];
        ans+=tmp;  ans+=rtmp;  ans+=cur[0];
        cout<<ans<<endl;
    }
    else if(cur.size()==5)
    {
        string tmp="",ans="",rtmp;
        for(int i=0;i<26;i++) 
            for(int j=0;j<ensure[i]/4;j++) 
                tmp+=(char)('a'+i);
        rtmp=tmp; reverse(rtmp.begin(),rtmp.end()); 
        ans+=cur[0]; ans+=tmp; ans+=cur[1]; ans+=rtmp;  ans+=cur[0];
        ans+=tmp; ans+=cur[1]; ans+=rtmp;  ans+=cur[0];
        cout<<ans<<endl;
    }
    return 0;
}