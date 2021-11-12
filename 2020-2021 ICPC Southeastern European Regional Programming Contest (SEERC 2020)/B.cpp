#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
string s;
int main()
{
    cin>>s;
    ll res=0,cnt=(int)s.size()-1;
    for(int i=0;i<(int)s.size();i++)
        if(s[i]=='1') res+=(cnt-i),cnt--;
    if(res%3==0) puts("Bob"); else puts("Alice");
    return 0;
}