#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,ll> P;
ll aa,bb;
mt19937 wcy(time(NULL));
int type=0;
vector<P> ans;
int main()
{
    scanf("%lld%lld",&aa,&bb);
    for(int iter=0;iter<=20000;iter++)
    {
        ans.clear();
        ll a=aa,b=bb;
        type=0;
        int t=0,cnt=0;
        while(a!=0&&b!=0)
        {
            if(max(-a,a)<max(-b,b))
            {
                swap(a,b);
                type^=1;
            }
            ll k=max(-a,a)/max(-b,b);
            if(wcy()&1)
            {
                if(a<0&&b<0) {a-=k*b; ans.push_back(P(type,-k));}
                else if(a<0&&b>0) {a+=k*b; ans.push_back(P(type,k));}
                else if(a>0&&b<0) {a+=k*b; ans.push_back(P(type,k));}
                else if(a>0&&b>0) {a-=k*b; ans.push_back(P(type,-k));}
            }
            else
            {
                if(a<0&&b<0) {a-=(k+1)*b; ans.push_back(P(type,-(k+1)));}
                else if(a<0&&b>0) {a+=(k+1)*b; ans.push_back(P(type,k+1));}
                else if(a>0&&b<0) {a+=(k+1)*b; ans.push_back(P(type,k+1));}
                else if(a>0&&b>0) {a-=(k+1)*b; ans.push_back(P(type,-(k+1)));}
            }
            cnt++;
            if(cnt>50) break;
        }
        if(cnt<=50)
        {
            printf("%d\n",cnt);
            for(auto p:ans) printf("%d %lld\n",p.F+1,p.S);
            return 0;
        }
    }
    return 0;
}