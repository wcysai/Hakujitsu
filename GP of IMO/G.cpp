#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<2000> bs;
int n;
//x1,x2,x3,x4,x5,x6
string str[MAXN];
bs a[MAXN],b[MAXN];
ll c1,c2,c3,c4;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) 
    {
        cin>>str[i];
        a[i].reset(); b[i].reset();
        for(int j=0;j<n;j++) if(str[i][j]=='Y') a[i].set(j); else if (str[i][j]=='B') b[i].set(j);
    }
    c1=1LL*n*(n-1)*(n-2)*(n-3)/24;
    c2=c3=c4=0;
    for(int i=0;i<n;i++) c2+=2LL*(n-3)*a[i].count()*b[i].count();
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
        {
            if(a[i].test(j))//yellow
            {
                int num=(a[i]&a[j]).count();
                c3+=2LL*num*(num-1);
            }
            else
            {
                int num=(b[i]&b[j]).count();
                c3+=2LL*num*(num-1);
            }
        }
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
        {
            if(a[i].test(j))//yellow
            {
                int num=(b[i]&b[j]).count();
                c4+=2LL*num*(num-1);
            }
            else
            {
                int num=(a[i]&a[j]).count();
                c4+=2LL*num*(num-1);
            }
        }
    c2/=4; c3/=4; c4/=4;
    printf("%lld\n",-3*c1+c2+(c3-c4)/2);
    return 0;
}