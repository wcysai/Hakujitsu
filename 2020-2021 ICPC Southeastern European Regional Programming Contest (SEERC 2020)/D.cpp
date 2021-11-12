#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define fixed adkoa
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
vector<int> rods[MAXN];
bool fixed[MAXN];
set<P> v[MAXN];
vector<P> ans;
bool cmp(P x,P y)
{
    return x.S<y.S;
}
void move(int x,int y)
{
    ans.push_back(P(x,y));
    int val=rods[x].back();
    v[val].erase(v[val].find(P(x,3-(int)rods[x].size())));
    rods[x].pop_back();
    rods[y].push_back(val);
    v[val].insert(P(y,3-(int)rods[y].size()));
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<3;i++)
        for(int j=1;j<=n;j++)
        {
            int x;
            scanf("%d",&x);
            rods[j].push_back(x);
        }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<3;j++) 
            v[rods[i][j]].insert(P(i,j));
        reverse(rods[i].begin(),rods[i].end());
    }
    memset(fixed,false,sizeof(fixed));
    int empt=n+1;
    for(int i=1;i<=n-1;i++)
    {
        int id=-1;
        vector<P> tmp;
        for(int j=1;j<=n;j++)
        {
            if(fixed[j]) continue;
            vector<P> vv;
            for(auto p:v[j]) vv.push_back(p);
            sort(vv.begin(),vv.end(),cmp);
            if(vv[1].S==2&&vv[2].S==2) continue;
            if(vv[0].S==0) {id=j; tmp=vv; break;}
        }
        if(tmp[0].F==tmp[1].F&&tmp[0].F==tmp[2].F) {fixed[id]=true; continue;}
        if(tmp[2].S==0)
        {
            move(tmp[0].F,empt); move(tmp[1].F,empt); move(tmp[2].F,empt);
            move(tmp[0].F,tmp[1].F); move(tmp[0].F,tmp[2].F);
            empt=tmp[0].F; fixed[id]=true; continue;
        }
        vector<int> holes;
        move(tmp[0].F,empt); holes.push_back(tmp[0].F);
        if(tmp[1].S==0)
        {
            move(tmp[1].F,empt); 
            if(tmp[2].F==tmp[0].F)
            {
                if(tmp[2].S==1)
                {
                    move(tmp[0].F,empt); move(tmp[0].F,tmp[1].F);
                    empt=tmp[0].F; fixed[id]=true; continue;
                }
                move(tmp[1].F,tmp[0].F); holes.pop_back(); holes.push_back(tmp[1].F); holes.push_back(tmp[1].F);
            }
            else if(tmp[2].F==tmp[1].F)
            {
                if(tmp[2].S==1)
                {
                    move(tmp[1].F,empt); move(tmp[1].F,tmp[0].F);
                    empt=tmp[1].F; fixed[id]=true; continue;
                }
                move(tmp[0].F,tmp[1].F); holes.push_back(tmp[0].F); 
            }
            else
            {
                move(tmp[0].F,tmp[1].F); holes.push_back(tmp[0].F); 
            }
        }
        else
        {
            if(tmp[1].F==tmp[0].F) {move(tmp[0].F,empt); holes.push_back(tmp[0].F);} else 
            {
                move(tmp[1].F,holes.back()); holes.pop_back(); holes.push_back(tmp[1].F);
                move(tmp[1].F,empt); holes.push_back(tmp[1].F);
            }
        }
        //hole: two of the same kind
        if(tmp[2].S==1)
        {
            move(tmp[2].F,holes.back()); move(tmp[2].F,empt); move(tmp[2].F,holes.back());
        }
        else
        {
            if(tmp[2].F==holes.back())
            {
                move(tmp[2].F,empt);
            }
            else
            {
                move(tmp[2].F,holes.back()); move(tmp[2].F,holes.back()); move(tmp[2].F,empt); 
            }
        }
        empt=tmp[2].F;
        fixed[id]=true;
    }
    if(empt!=n+1)
    {
        move(n+1,empt); move(n+1,empt); move(n+1,empt);
    }
    printf("%d\n",(int)ans.size());
    for(auto p:ans) printf("%d %d\n",p.F,p.S);
    return 0;
}