#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,a,b,ans[MAXN];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&a,&b);
        if(a+b>n-2||max(a-b,b-a)>1) {puts("-1"); continue;}
        else if(a>=b)
        {
            int l=1,r=n;
            for(int i=1;i<=a;i++) ans[2*i]=r,r--;
            for(int i=1;i<=b;i++) ans[2*i+1]=l,l++;
            ans[1]=l; l++;
            int last=max(2*b+1,2*a);
            if(2*b+1>=2*a)
            {
                for(int i=last+1;i<=n;i++) ans[i]=l,l++;
            }
            else
            {
                for(int i=last+1;i<=n;i++) ans[i]=r,r--;
            }
        }
        else
        {
            int l=1,r=n;
            for(int i=1;i<=a;i++) ans[2*i+1]=r,r--;
            for(int i=1;i<=b;i++) ans[2*i]=l,l++;
            int last=max(2*b,2*a+1);
            ans[1]=r; r--;
            for(int i=last+1;i<=n;i++) ans[i]=l,l++;
        }
        for(int i=1;i<=n;i++) printf("%d%c",ans[i],i==n?'\n':' ');
    }
    return 0;
}