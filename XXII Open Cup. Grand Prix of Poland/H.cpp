#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
string str;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        cin>>str;
        for(int i=0;i<(int)str.size();i++)
            str[i]=(str[i]-'a'+13)%26+'a';
        cout<<str<<endl;
    }
    return 0;
}