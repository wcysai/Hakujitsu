#include<bits/stdc++.h>
#define MAXN 1005
#define MAXM (1<<20)
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
char str[MAXN+1];
int rightmost[21];
int maxright[MAXM],sz;
P dp[MAXM];
map<char,char> mp;
vector<int> masks[21];
int cnt[21][MAXN];
int pre[21][MAXN];
vector<int> ans;
int main()
{
    scanf("%d",&n);
    scanf("%s",str+1);
    int t=0;
    for(int i=1;i<=n;i++)
    {
        if(mp.find(str[i])==mp.end()) 
        {
            mp[str[i]]=(char)('a'+t);
            t++;
        }
    }
    for(int i=1;i<=n;i++) str[i]=mp[str[i]];
    sz=(int)mp.size();
    for(int i=0;i<(1<<sz);i++) masks[__builtin_popcount(i)].push_back(i);
    for(int i=n;i>=1;i--) if(!rightmost[str[i]-'a']) rightmost[str[i]-'a']=i;
    for(int mask=0;mask<(1<<sz);mask++)
    {
        int r=n+1;
        for(int i=0;i<sz;i++)
            if(mask&(1<<i)) r=min(r,rightmost[i]);
        maxright[mask]=r;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<sz;j++) pre[j][i]=pre[j][i-1];
        for(int j=0;j<sz;j++) cnt[j][i]=cnt[j][i-1];
        pre[str[i]-'a'][i]=i;
        cnt[str[i]-'a'][i]++;
    }
    vector<int> valid; valid.push_back(0);
    int all=(1<<sz)-1;
    dp[0]=P(0,0);
    for(int i=1;i<=sz;i++)
    {
        int maxi=0;
        for(auto mask:valid)
        {
            for(int j=0;j<sz;j++)
            {
                if(!(mask&(1<<j)))
                {
                    int pos=pre[j][maxright[all^(mask|(1<<j))]-1];
                    int num=cnt[j][pos]-cnt[j][dp[mask].S];
                    if(num<=0) continue;
                    if(num>dp[mask^(1<<j)].F||(num==dp[mask^(1<<j)].F&&pos<dp[mask^(1<<j)].S))
                    {
                        dp[mask^(1<<j)]=P(num,pos);
                        maxi=max(maxi,num);
                    }
                }
            }
        }
        valid.clear();
        ans.push_back(maxi);
        for(auto mask:masks[i]) if(dp[mask].F==maxi) valid.push_back(mask);
    }
    for(int i=0;i<sz;i++) 
        for(int j=0;j<ans[i];j++)
            printf("%c",'a'+sz-i-1);
    return 0;
}