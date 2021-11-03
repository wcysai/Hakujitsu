#include<bits/stdc++.h>
#define MAXN 4005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<short,short> P;
typedef bitset<4000> bs;
int n,cost[MAXN][MAXN];
int dp[MAXN][MAXN];
bs cpl[MAXN],cpr[MAXN],ucpl[MAXN],ucpr[MAXN];
void upd(int &a,int b) {a=min(a,b);}
vector<P> que[MAXN*MAXN/4];
inline bool scan_d(int &num)  
{
        char in;bool IsN=false;
        in=getchar();
        if(in==EOF) return false;
        while(in!='-'&&(in<'0'||in>'9')) in=getchar();
        if(in=='-'){ IsN=true;num=0;}
        else num=in-'0';
        while(in=getchar(),in>='0'&&in<='9'){
                num*=10,num+=in-'0';
        }
        if(IsN) num=-num;
        return true;
}
int main()
{
    scan_d(n);
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j+=2)
            scan_d(cost[i][j]);
    for(int i=0;i<n;i++) cpl[i].reset(),cpr[i].reset(),ucpl[i].reset(),ucpr[i].reset();
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j+=2)
        {
            ucpl[i].set(j);
            ucpr[j].set(i);
            if(j==i+1) {dp[i][j]=cost[i][j]; que[cost[i][j]].push_back(P(i,j)); ucpl[i].reset(j); ucpr[j].reset(i);} else dp[i][j]=INF;
        }
    for(int val=1;val<=n*n/4;val++)
    {
        for(int i=0;i<(int)que[val].size();i++)
        {
            P p=que[val][i];
            int l=p.F,r=p.S;
            if(dp[l][r]!=val) continue;
            //set as computed
            cpl[l].set(r); cpr[r].set(l);
            ucpl[l].reset(r); ucpr[r].reset(l);
            //make transition of double ends
            if(l>0&&r<n-1&&ucpl[l-1].test(r+1)) 
            {
                dp[l-1][r+1]=max(val,cost[l-1][r+1]);
                que[dp[l-1][r+1]].push_back(P(l-1,r+1));
            }
            //make transitions to the right
            if(r+1<n)
            {
                bs tmp=ucpl[l]&cpl[r+1];
                for(int k=tmp._Find_next(r);k<n;k=tmp._Find_next(k))
                {
                    dp[l][k]=val;
                    ucpr[k].reset(l); ucpl[l].reset(k);
                    que[val].push_back(P(l,k));
                }
            }
            //make transitions to the left
            if(l>0)
            {
                bs tmp=ucpr[r]&cpr[l-1];
                for(int k=tmp._Find_first();k<l;k=tmp._Find_next(k))
                {
                    dp[k][r]=val;
                    ucpl[k].reset(r); ucpr[r].reset(k);
                    que[val].push_back(P(k,r));
                }
            }
        }
    }
    printf("%d\n",dp[0][n-1]);
    return 0;
}