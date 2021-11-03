#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
string str;
int match[MAXN];
vector<int> v;
int get_order(int l,int r)
{
    if(l+1==r)
    {
        assert(str[l]=='('&str[r]==')');
        return 0;
    }
    if(str[l]=='('&&match[l]==r) return get_order(l+1,r-1);
    int id=-1,last=-1;
    for(int i=l;i<r;i++)
    {
        if(str[i]=='-'&&i>last)
        {
            id=i;
            break;
        }
        else if(str[i]=='(') last=max(last,match[i]);
    }
    assert(id!=-1);
    return max(get_order(l,id-1)+1,get_order(id+2,r));
}
int main()
{
    cin>>str;
    int sz=(int)str.size();
    for(int i=0;i<sz;i++)
    {
        if(str[i]=='(') v.push_back(i);
        else if(str[i]==')')
        {
            int last=v.back(); v.pop_back();
            match[last]=i;
        }
    }
    printf("%d\n",get_order(0,sz-1));
}