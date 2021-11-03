#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include <bits/extc++.h>
using namespace __gnu_pbds;
#define MAXN 200005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
char str[MAXN];
int base[2]={233,666};
int MOD[2]={993244853,993244353};
int pw[2][MAXN];
int hsh[2][MAXN];

unordered_map<ll,int> cnthash,cntwild;

struct SA{
    int s[MAXN];
    int sa[MAXN], t[MAXN], t2[MAXN], c[MAXN], n;
    int r[MAXN], h[MAXN];
    int mn[MAXN][25];
    int lg[MAXN];

    void build_sa(int n, int m) {
        int *x = t, *y = t2;
        for (int i = 0; i < m; i += 1) {
            c[i] = 0;
        }
        for (int i = 0; i < n; i += 1) {
            c[x[i] = s[i]] += 1;
        }
        for (int i = 1; i < m; i += 1) {
            c[i] += c[i - 1];
        }
        for (int i = n - 1; i >= 0; i -= 1) {
            sa[--c[x[i]]] = i;
        }
        for (int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for (int i = n - k; i < n; i += 1) y[p++] = i;
            for (int i = 0; i < n; i += 1) {
                if(sa[i] >= k) y[p++] = sa[i] - k;
            }
            for (int i = 0; i < m; i += 1) {
                c[i] = 0;
            }
            for (int i = 0; i < n; i += 1) {
                c[x[y[i]]] += 1;
            }
            for (int i = 0; i < m; i += 1) {
                c[i] += c[i - 1];
            }
            for (int i = n - 1; i >= 0; i -= 1) {
                sa[--c[x[y[i]]]] = y[i];
            }
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for (int i = 1; i < n; i += 1) {
                x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
            }
            if(p >= n) break;
            m = p;
        }
    }

    void getheight(int n){
        int i, j, k = 0;
        for (i = 1; i <= n; i += 1) {
            r[sa[i]] = i;
        }
        for (i = 0; i < n; h[r[i++]] = k) {
            for(k ? k-- : 0, j = sa[r[i] - 1]; s[i + k] == s[j + k]; k += 1);
        }
    }

    void build_rmq(int n){
        for (int i = 2; i < MAXN; i += 1) {
            lg[i] = lg[i >> 1] + 1;
        }
        for (int i = 1; i <= n; i += 1) {
            mn[i][0] = h[i];
        }
        for (int j = 1; (1 << j) <= n; j += 1) {
            for (int i = 1; i + (1 << j) - 1 <= n; i += 1) {
                mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int qmin(int L, int R){
        if(L > R) swap(L, R);
        int k = lg[R - L + 1];
        return min(mn[L][k], mn[R - (1 << k) + 1][k]);
    }
    int lcp(int i, int j) {
        
        if(i == j) return n - sa[i];
        //cerr << i << " " << j << endl;
        i = r[i];
        j = r[j];
        if(i > j) swap(i, j);
        //cerr << i << " " << j << endl;
        return qmin(i + 1, j);
    }

    void test(){
        int n;
        cin >> n;
        for (int i = 0; i < n; i += 1) {
            cin >> s[i];
        }
        s[n] = 0;
        build_sa(n + 1, 100);
        getheight(n);
        build_rmq(n);
    }
}sol;

const int threshold=200;
P get_hash(string &str)
{
    int h[2]={0,0};
    for(int i=0;i<(int)str.size();i++) 
        for(int j=0;j<2;j++) h[j]=(1LL*h[j]*base[j]+(str[i]-'a'+1))%MOD[j];
    return P(h[0],h[1]);
}
P get_hash(int l,int r)
{
    int h[2];
    for(int i=0;i<2;i++)
    {
        h[i]=(hsh[i][r]-1LL*hsh[i][l-1]*pw[i][r-l+1]%MOD[i]);
        if(h[i]<0) h[i]+=MOD[i];
    }
    return P(h[0],h[1]);
}

int main()
{   
    //freopen("B.in","r",stdin);
    //clock_t startTime,endTime;
    //  startTime = clock();
    scanf("%d",&n);
    scanf("%s",str+1);
    for (int i = 1; i <= n; i += 1) {
        sol.s[i - 1] = str[i] - '0' + 1;
    }
    sol.s[n] = 0;
    
    sol.build_sa(n + 1, 1000);
    sol.getheight(n);
    sol.build_rmq(n);

    for(int i=0;i<2;i++)
    {
        pw[i][0]=1;
        for(int j=1;j<=n;j++) pw[i][j]=1LL*pw[i][j-1]*base[i]%MOD[i];
    }
    for(int i=0;i<2;i++)
    {
        hsh[i][0]=0;
        for(int j=1;j<=n;j++) hsh[i][j]=(1LL*hsh[i][j-1]*base[i]+(str[j]-'a'+1))%MOD[i];
    }
    //k<=threshold
    for(int i=1;i<=min(threshold,n);i++)
    {
        cnthash.clear(); cntwild.clear();
        for(int j=1;i*j<=n;j++)
        {
            int l=(j-1)*i+1,r=l+i-1;
            P p=get_hash(l,r);
            cnthash[1LL*p.F*INF+p.S]++;
            for(int pos=0;pos<i;pos++)
            {
                P q;
                q.F=(p.F+1LL*pw[0][i-pos-1]*(26-(str[pos+l]-'a')))%MOD[0]; if(q.F<0) q.F+=MOD[0];
                q.S=(p.S+1LL*pw[1][i-pos-1]*(26-(str[pos+l]-'a')))%MOD[1]; if(q.S<0) q.S+=MOD[1];
                cntwild[1LL*q.F*INF+q.S]++;
            }
        }
        ll ans=0;
        for(int j=1;i*j<=n;j++)
        {
            int l=(j-1)*i+1,r=l+i-1;
            P p=get_hash(l,r);
            ans--;
            ans-=1LL*cnthash[1LL*p.F*INF+p.S]*(i-1);
            for(int pos=0;pos<i;pos++)
            {
                P q;
                q.F=(p.F+1LL*pw[0][i-pos-1]*(26-(str[pos+l]-'a')))%MOD[0]; if(q.F<0) q.F+=MOD[0];
                q.S=(p.S+1LL*pw[1][i-pos-1]*(26-(str[pos+l]-'a')))%MOD[1]; if(q.S<0) q.S+=MOD[1];
                ans+=cntwild[1LL*q.F*INF+q.S];
            }
        }
        printf("%lld ",ans/2);
    }
    //endTime = clock();//计时结束
    // cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    for(int i=threshold+1;i<=n;i++)
    {
        //printf("i=%d\n",i);
        ll ans=0;
        for(int j=1;i*j<=n;j++)
            for(int k=j+1;i*k<=n;k++)
            {
                int l1=(j-1)*i+1,r1=l1+i-1,l2=(k-1)*i+1,r2=l2+i-1;
                P p=get_hash(l1,r1); P q=get_hash(l2,r2);
                int lcp = sol.lcp(l1 - 1, l2 - 1);
                int len = min(r1 - l1 + 1, r2 - l2 + 1);
                //printf("lcp=%d\n",lcp);
                int can = 0;
                if(lcp >= len) {
                    can = 1;
                }
                else{
                    int lcp2 = sol.lcp(l1 + lcp, l2 + lcp);
                    if(lcp + lcp2 + 1 >= len) {
                        can = 1;
                    }
                }
                ans += can;
            }
        printf("%lld ",ans);
    }
    //endTime = clock();//计时结束
    //cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}