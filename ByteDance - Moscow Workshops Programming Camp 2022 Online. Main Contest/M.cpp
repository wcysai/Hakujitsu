#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,x[MAXN],y[MAXN],c[MAXN];
vector<P> colr[3];//sort by row
vector<P> colc[3];//sort by col
vector<int> res;
map<pair<P,int>,int> mp;
int perm[3],save[3];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d%d%d",&x[i],&y[i],&c[i]);
        mp[make_pair(P(x[i],y[i]),c[i])]=i;
        colr[c[i]-1].push_back(P(x[i],y[i]));
        colc[c[i]-1].push_back(P(y[i],x[i]));
    }
    for(int i=0;i<3;i++) sort(colr[i].begin(),colr[i].end());
    for(int i=0;i<3;i++) sort(colc[i].begin(),colc[i].end());
    for(int i=0;i<3;i++)
        for(int j=0;j<(int)colc[i].size();j++)
            swap(colc[i][j].F,colc[i][j].S);
    int ans=0;
    int l=0,r=n/3;
    // | |
    while(r-l>1)
    {
        int mid=(l+r)/2;
        perm[0]=0; perm[1]=1; perm[2]=2;
        bool f=false;
        do
        {
            int posl=colr[perm[0]][mid-1].F;
            int posr=colr[perm[2]][colr[perm[2]].size()-mid].S;
            int cnt=0;
            for(auto x:colr[perm[1]]) if(x.F>=posl&&x.F<=posr) cnt++;
        }while(next_permutation(perm,perm+3));
        if(f) 
        {
            l=mid; 
            for(int i=0;i<3;i++) save[i]=perm[i];
        }
        else r=mid;
    }
    if(l>ans)
    {
        ans=l;
        res.clear();
        int posl=colr[save[0]][l-1].F;
        int posr=colr[save[2]][colr[save[2]].size()-l].S;
        for(int i=0;i<l;i++) res.push_back(mp[make_pair(colr[save[0]][i],save[0])]);
        for(int i=(int)colr[save[2]].size()-1;i>=colr[perm[2]].size()-l;i--) res.push_back(mp[make_pair(colr[save[2]][i],save[2])]);
        int cnt=0;
        for(auto x:colr[save[1]]) 
        {
            if(x.F>=posl&&x.F<=posr) 
            {
                res.push_back(mp[make_pair(x,save[1])]);
                cnt++;
            }
            if(cnt==l) break;
        }
    }
    // - -
    l=0,r=n/3;
    while(r-l>1)
    {
        if(r-1<=ans) break;
        int mid=(l+r)/2;
        perm[0]=0; perm[1]=1; perm[2]=2;
        bool f=false;
        do
        {
            int posl=colc[perm[0]][mid-1].F;
            int posr=colc[perm[2]][colr[perm[2]].size()-mid].S;
            int cnt=0;
            for(auto x:colr[perm[1]]) if(x.S>=posl&&x.S<=posr) cnt++;
            if(cnt>=mid) {f=true; break;}
        }while(next_permutation(perm,perm+3));
        if(f) l=mid; else r=mid;
    }
    if(l>ans)
    {
        ans=l;
        res.clear();
        int posl=colc[save[0]][l-1].F;
        int posr=colc[save[2]][colr[save[2]].size()-l].S;
        for(int i=0;i<l;i++) res.push_back(mp[make_pair(colc[save[0]][i],save[0])]);
        for(int i=(int)colc[save[2]].size()-1;i>=colc[perm[2]].size()-l;i--) res.push_back(mp[make_pair(colc[save[2]][i],save[2])]);
        int cnt=0;
        for(auto x:colc[save[1]]) 
        {
            if(x.F>=posl&&x.F<=posr) 
            {
                res.push_back(mp[make_pair(x,save[1])]);
                cnt++;
            }
            if(cnt==l) break;
        }
    }
    // |--
    l=0,r=n/3;
    while(r-l>1)
    {
        if(r-1<=ans) break;
        int mid=(l+r)/2;
        perm[0]=0; perm[1]=1; perm[2]=2;
        bool f=false;
        do
        {
            int posl=colr[perm[0]][mid-1].F;
            int cnt=0,posr;
            for(int i=0;i<(int)colc[perm[1]].size();i++) 
            {
                if(colc[perm[1]][i].F<posl) continue;
                cnt++; if(cnt==mid) {posr=colc[perm[1]][i].S; break;}
            }
            if(cnt<mid) continue;
            cnt=0;
            for(auto x:colr[perm[2]]) if(x.F>=posl&&x.S>=posr) cnt++;
            if(cnt>=mid) {f=true; break;}
        }while(next_permutation(perm,perm+3));
        if(f) l=mid; else r=mid;
    }
    if(l>ans)
    {
        ans=l;
        res.clear();
        int posl=colr[save[0]][l-1].F;
        for(int i=0;i<l;i++) res.push_back(mp[make_pair(colr[save[0]][i],save[0])]);
        int cnt=0,posr;
        for(int i=0;i<(int)colc[save[1]].size();i++) 
        {
            if(colc[save[1]][i].F<posl) continue;
            cnt++; 
            res.push_back(mp[make_pair(colc[save[1]][i],save[1])]);
            if(cnt==l) {posr=colc[save[1]][i].S; break;}
        }
        cnt=0;
        for(auto x:colr[save[2]]) 
            if(x.F>=posl&&x.S>=posr) 
            {
                cnt++;
                res.push_back(mp[make_pair(x,save[2])]);
            }
    }
    //--|
    l=0,r=n/3;
    while(r-l>1)
    {
        if(r-1<=ans) break;
        int mid=(l+r)/2;
        perm[0]=0; perm[1]=1; perm[2]=2;
        bool f=false;
        do
        {
            int posl=colr[perm[0]][colr[perm[0]].size()-mid].F;
            int cnt=0,posr;
            for(int i=0;i<(int)colc[perm[1]].size();i++) 
            {
                if(colc[perm[1]][i].F>posl) continue;
                cnt++; if(cnt==mid) {posr=colc[perm[1]][i].S; break;}
            }
            if(cnt<mid) continue;
            cnt=0;
            for(auto x:colr[perm[2]]) if(x.F<=posl&&x.S>=posr) cnt++;
            if(cnt>=mid) {f=true; break;}
        }while(next_permutation(perm,perm+3));
        if(f) l=mid; else r=mid;
    }
    if(l>ans)
    {
        ans=l;
        res.clear();
        int posl=colr[save[0]][colr[save[0]].size()-l].F;
        for(int i=0;i<l;i++) res.push_back(mp[make_pair(colr[save[0]][i],save[0])]);
        int cnt=0,posr;
        for(int i=0;i<(int)colc[save[1]].size();i++) 
        {
            if(colc[save[1]][i].F>posl) continue;
            cnt++; 
            res.push_back(mp[make_pair(colc[save[1]][i],save[1])]);
            if(cnt==l) {posr=colc[save[1]][i].S; break;}
        }
        cnt=0;
        for(auto x:colr[save[2]]) 
            if(x.F<=posl&&x.S>=posr) 
            {
                cnt++;
                res.push_back(mp[make_pair(x,save[2])]);
            }
    }
    
    // ---
    //  |
    l=0,r=n/3;
    while(r-l>1)
    {
        if(r-1<=ans) break;
        int mid=(l+r)/2;
        perm[0]=0; perm[1]=1; perm[2]=2;
        bool f=false;
        do
        {
            int posl=colc[perm[0]][mid-1].S;
            int cnt=0,posr;
            for(int i=0;i<(int)colr[perm[1]].size();i++) 
            {
                if(colr[perm[1]][i].S<posl) continue;
                cnt++; if(cnt==mid) {posr=colr[perm[1]][i].F; break;}
            }
            if(cnt<mid) continue;
            cnt=0;
            for(auto x:colc[perm[2]]) if(x.S>=posl&&x.F>=posr) cnt++;
            if(cnt>=mid) {f=true; break;}
        }while(next_permutation(perm,perm+3));
        if(f) l=mid; else r=mid;
    }
    if(l>ans)
    {
        ans=l;
        res.clear();
        int posl=colr[save[0]][colr[save[0]].size()-l].F;
        for(int i=0;i<l;i++) res.push_back(mp[make_pair(colr[save[0]][i],save[0])]);
        int cnt=0,posr;
        for(int i=0;i<(int)colc[save[1]].size();i++) 
        {
            if(colc[save[1]][i].F>posl) continue;
            cnt++; 
            res.push_back(mp[make_pair(colc[save[1]][i],save[1])]);
            if(cnt==l) {posr=colc[save[1]][i].S; break;}
        }
        cnt=0;
        for(auto x:colr[save[2]]) 
            if(x.F<=posl&&x.S>=posr) 
            {
                cnt++;
                res.push_back(mp[make_pair(x,save[2])]);
            }
    }
    
    // _|_
    l=0,r=n/3;
    while(r-l>1)
    {
        if(r-1<=ans) break;
        int mid=(l+r)/2;
        perm[0]=0; perm[1]=1; perm[2]=2;
        bool f=false;
        do
        {
            int posl=colc[perm[0]][colc[perm[0]].size()-mid].S;
            int cnt=0,posr;
            for(int i=0;i<(int)colr[perm[1]].size();i++) 
            {
                if(colr[perm[1]][i].S>posl) continue;
                cnt++; if(cnt==mid) {posr=colr[perm[1]][i].F; break;}
            }
            if(cnt<mid) continue;
            cnt=0;
            for(auto x:colc[perm[2]]) if(x.S<=posl&&x.F>=posr) cnt++;
            if(cnt>=mid) {f=true; break;}
        }while(next_permutation(perm,perm+3));
        if(f) l=mid; else r=mid;
    }
    ans=max(ans,l);
    return 0;
}