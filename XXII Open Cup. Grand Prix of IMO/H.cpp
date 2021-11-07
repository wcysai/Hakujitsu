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
int calc(int x)
{
    return x*(x-1)/2+2*(x-1);
}
int main()
{
    scanf("%d",&n);
    if(n==1)
    {
        printf("%d %d\n%d %d\n",2,1,1,2);
    }
    else if(n==2)
    {
        printf("%d %d\n",4,4);
        printf("%d %d\n",1,2);
        printf("%d %d\n",2,3);
        printf("%d %d\n",1,3);
        printf("%d %d\n",1,4);
    }
    else if(n<=20)
    {
        printf("%d %d\n",n,n);
        for(int i=1;i<=n;i++) printf("%d %d\n",i,i==n?1:i+1);
    }
    else
    {
        int now=3;
        while(calc(now+1)<=n) now++;
        int rem=n-calc(now)+2;
        assert(rem+now<=20);
        printf("%d %d\n",now+rem,now*(now-1)/2+rem+1); 
        for(int i=1;i<=now;i++)
            for(int j=i+1;j<=now;j++)
                printf("%d %d\n",i,j);
        if(rem)
        {
            for(int i=1;i<=rem-1;i++) printf("%d %d\n",now+i,now+i+1);
            printf("%d %d\n",now-1,now+1);
            printf("%d %d\n",now,now+rem);
        }
    }
    return 0;
}