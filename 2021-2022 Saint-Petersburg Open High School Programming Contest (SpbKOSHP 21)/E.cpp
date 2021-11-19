#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
string str[MAXN];
int cnt[MAXN];
set<char> vowels;
int get_phonetic(string s)
{
    int cnt=0,flag=0;
    for(int i=0;i<(int)s.size();i++)
    {
        if(vowels.count(s[i]))
        {
            if(!flag) cnt++;
            flag=1;
        } 
        else flag=0;
    }
    return cnt;
}
int get_five(int x)
{
    int c=0;
    for(int i=x;i<n;i++)
    {
        c+=cnt[i];
        if(c==5) return i+1;
        if(c>5) return -1;
    }
    return -1;
}
int get_seven(int x)
{
    int c=0;
    for(int i=x;i<n;i++)
    {
        c+=cnt[i];
        if(c==7) return i+1;
        if(c>7) return -1;
    }
    return -1;
}
int main()
{
    vowels.insert('a'); vowels.insert('e'); vowels.insert('i'); vowels.insert('o'); vowels.insert('u');
    scanf("%d",&n);
    int ans=0;
    for(int i=0;i<n;i++) 
    {
        cin>>str[i];
        cnt[i]=get_phonetic(str[i]);
    }
    for(int i=0;i<n;i++)
    {
        int x=get_five(i); if(x==-1) continue;
        x=get_seven(x); if(x==-1) continue;
        x=get_five(x); if(x==-1) continue;
        ans++;
    }
    printf("%d\n",ans);
    return 0;
}