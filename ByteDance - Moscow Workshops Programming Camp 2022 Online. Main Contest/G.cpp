// #pragma comment(linker, "/STACK:102400000,102400000")
#pragma GCC optimize("O3","trapv")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>

#define int long long
using namespace std;
 
#define rep(i,n) for (int i=0;i<(int)(n);++i)
#define rep1(i,n) for (int i=1;i<=(int)(n);++i)
#define range(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
 
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
const int maxn=100007;
// const int mod=998244353;
const int INF=LLONG_MAX/4;
int p[]={39971, 39953, 39901};
map<pii,int> s,s2;
int modpow(int u,int v,int mod){
    int ans=1, t=u;
    while (v){
        if (v&1) ans=ans*t%mod;
        t=t*t%mod, v>>=1;
    }
    return ans;
}

signed main(){
    for (int i=1;i<=100000;++i){
        pii ret=make_pair(modpow(i,i,p[0]),modpow(i,i,p[1]));
        if (modpow(i,i,p[0])==10173||modpow(i,i,p[0])==24631||modpow(i,i,p[0])==21577||modpow(i,i,p[0])==27474||modpow(i,i,p[0])==32491||modpow(i,i,p[0])==35540){
            ret=make_pair(modpow(i,i,p[0]),modpow(i,i,p[2]));
            if (s2.find(ret)!=s2.end()){
                assert(0);
            }
            s2[ret]=i;
        }
        else{
            assert(s.find(ret)==s.end());
            s[ret]=i;
        }
    }
    int _;
    cin>>_;
    while (_--){
        cout<<"? "<<p[0]<<endl;
        int x;
        cin>>x;
        if (x==10173||x==24631||x==21577||x==27474||x==32491||x==35540){
            cout<<"? "<<p[2]<<endl;
            int y;
            cin>>y;
            int ans=s2[{x,y}];
            assert(ans>0);
            cout<<"! "<<ans<<endl;
        }
        else{
            cout<<"? "<<p[1]<<endl;
            int y;
            cin>>y;
            int ans=s[{x,y}];
            cout<<"! "<<ans<<endl;
        }
        int z;
        cin>>z;
    }
    return 0;
}