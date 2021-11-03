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
mt19937 wcy(time(NULL));
vector<int> v;
int seed[MAXN];
int ask()
{
    printf("? %d",(int)v.size());
    for(auto x:v) printf(" %d",x);
    printf("\n");
    fflush(stdout);
    int x;
    scanf("%d",&x);
    return x;
}
void answer(int x)
{
    if(x) printf("! YES\n"); else printf("! NO\n");
    fflush(stdout);
}
int main()
{  
    scanf("%d",&n);
    for(int i=1;i<=n;i++) v.push_back(i);
    int all=ask();
    bool valid=true;
    for(int i=0;i<29;i++)
    {
        for(int j=1;j<=n;j++) seed[j]=wcy()&1;
        v.clear();
        for(int j=1;j<=n;j++) if(seed[j]) v.push_back(j);
        int left=ask();
        v.clear();
        for(int j=1;j<=n;j++) if(!seed[j]) v.push_back(j);
        int right=ask();
        if((all-left-right)&1)
        {
            valid=false;
            break;
        }
    }
    if(valid) answer(1); else answer(0);
    return 0;
}