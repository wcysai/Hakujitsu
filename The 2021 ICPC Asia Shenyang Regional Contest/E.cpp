#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
string str;
int main()
{
    cin>>str;
    int ans=0;
    for(int i=0;i<(int)str.size()-4;i++) if(str.substr(i,5)=="edgnb") ans++;
    printf("%d\n",ans);
    return 0;
}