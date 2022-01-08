#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define F first
#define S second
#define int long long
using namespace std;
typedef long long ll;
typedef pair<double,double> P;
const double EPS=1e-9;
signed main(){
    cout.precision(15);
    vector<int> a,b;
    for (int i=0;i<4;++i){
        int u;
        cin>>u;
        u--;
        a.push_back(u);
    }
    b=a;
    sort(b.begin(),b.end());
    int ret1=b[0]*b[3], ret2=b[1]*b[2];
    vector<double> ret;
    for(auto c:b) ret.push_back(c);
    if (ret1!=ret2){
        if (ret1<ret2){
            ret[1]=1.0*ret1/ret[2];
        }
        else{
            ret[0]=1.0*ret2/ret[3];
        }
    }
    vector<int> perm(4);
    for (int i=0;i<4;++i) perm[i]=i;
    do{
        bool ok=1;
        for (int i=0;i<4;++i){
            if (a[perm[i]]<ret[i]-EPS) ok=0;
        }
        if (ok){
            for (auto c:perm) cout<<c+1<<" ";
            cout<<"\n";
            for (auto c:ret) cout<<c+1<<" ";
            return 0;
        }
    }while (next_permutation(perm.begin(),perm.end()));
}