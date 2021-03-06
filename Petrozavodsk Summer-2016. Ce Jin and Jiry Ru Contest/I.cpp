#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAXN 50005
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const double PI=acos(-1.0);
inline void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
inline void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
namespace fft
{
    struct num
    {
        double x,y;
        num() {x=y=0;}
        num(double x,double y):x(x),y(y){}
    };
    inline num operator+(num a,num b) {return num(a.x+b.x,a.y+b.y);}
    inline num operator-(num a,num b) {return num(a.x-b.x,a.y-b.y);}
    inline num operator*(num a,num b) {return num(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
    inline num conj(num a) {return num(a.x,-a.y);}

    int base=1;
    vector<num> roots={{0,0},{1,0}};
    vector<int> rev={0,1};
    const double PI=acosl(-1.0);

    void ensure_base(int nbase)
    {
        if(nbase<=base) return;
        rev.resize(1<<nbase);
        for(int i=0;i<(1<<nbase);i++)
            rev[i]=(rev[i>>1]>>1)+((i&1)<<(nbase-1));
        roots.resize(1<<nbase);
        while(base<nbase)
        {
            double angle=2*PI/(1<<(base+1));
            for(int i=1<<(base-1);i<(1<<base);i++)
            {
                roots[i<<1]=roots[i];
                double angle_i=angle*(2*i+1-(1<<base));
                roots[(i<<1)+1]=num(cos(angle_i),sin(angle_i));
            }
            base++;
        }
    }

    void fft(vector<num> &a,int n=-1)
    {
        if(n==-1) n=a.size();
        assert((n&(n-1))==0);
        int zeros=__builtin_ctz(n);
        ensure_base(zeros);
        int shift=base-zeros;
        for(int i=0;i<n;i++)
            if(i<(rev[i]>>shift))
                swap(a[i],a[rev[i]>>shift]);
        for(int k=1;k<n;k<<=1)
        {
            for(int i=0;i<n;i+=2*k)
            {
                for(int j=0;j<k;j++)
                {
                    num z=a[i+j+k]*roots[j+k];
                    a[i+j+k]=a[i+j]-z;
                    a[i+j]=a[i+j]+z;
                }
            }
        }
    }

    vector<num> fa,fb;

    vector<int> multiply(vector<int> &a, vector<int> &b)
    {
        int need=a.size()+b.size()-1;
        int nbase=0;
        while((1<<nbase)<need) nbase++;
        ensure_base(nbase);
        int sz=1<<nbase;
        if(sz>(int)fa.size()) fa.resize(sz);
        for(int i=0;i<sz;i++)
        {
            int x=(i<(int)a.size()?a[i]:0);
            int y=(i<(int)b.size()?b[i]:0);
            fa[i]=num(x,y);
        }
        fft(fa,sz);
        num r(0,-0.25/sz);
        for(int i=0;i<=(sz>>1);i++)
        {
            int j=(sz-i)&(sz-1);
            num z=(fa[j]*fa[j]-conj(fa[i]*fa[i]))*r;
            if(i!=j) fa[j]=(fa[i]*fa[i]-conj(fa[j]*fa[j]))*r;
            fa[i]=z;
        }
        fft(fa,sz);
        vector<int> res(need);
        for(int i=0;i<need;i++) res[i]=fa[i].x+0.5;
        return res;
    }

    vector<int> multiply_mod(vector<int> &a,vector<int> &b,int m,int eq=0)
    {
        int need=a.size()+b.size()-1;
        int nbase=0;
        while((1<<nbase)<need) nbase++;
        ensure_base(nbase);
        int sz=1<<nbase;
        if(sz>(int)fa.size()) fa.resize(sz);
        for(int i=0;i<(int)a.size();i++)
        {
            int x=(a[i]%m+m)%m;
            fa[i]=num(x&((1<<15)-1),x>>15);
        }
        fill(fa.begin()+a.size(),fa.begin()+sz,num{0,0});
        fft(fa,sz);
        if(sz>(int)fb.size()) fb.resize(sz);
        if(eq) copy(fa.begin(),fa.begin()+sz,fb.begin());
        else
        {
            for(int i=0;i<(int)b.size();i++)
            {
                int x=(b[i]%m+m)%m;
                fb[i]=num(x&((1<<15)-1),x>>15);
            }
            fill(fb.begin()+b.size(),fb.begin()+sz,num{0,0});
            fft(fb,sz);
        }
        double ratio=0.25/sz;
        num r2(0,-1),r3(ratio,0),r4(0,-ratio),r5(0,1);
        for(int i=0;i<=(sz>>1);i++)
        {
            int j=(sz-i)&(sz-1);
            num a1=(fa[i]+conj(fa[j]));
            num a2=(fa[i]-conj(fa[j]))*r2;
            num b1=(fb[i]+conj(fb[j]))*r3;
            num b2=(fb[i]-conj(fb[j]))*r4;
            if(i!=j)
            {
                num c1=(fa[j]+conj(fa[i]));
                num c2=(fa[j]-conj(fa[i]))*r2;
                num d1=(fb[j]+conj(fb[i]))*r3;
                num d2=(fb[j]-conj(fb[i]))*r4;
                fa[i]=c1*d1+c2*d2*r5;
                fb[i]=c1*d2+c2*d1;
            }
            fa[j]=a1*b1+a2*b2*r5;
            fb[j]=a1*b2+a2*b1;
        }
        fft(fa,sz);fft(fb,sz);
        vector<int> res(need);
        for(int i=0;i<need;i++)
        {
            ll aa=fa[i].x+0.5;
            ll bb=fb[i].x+0.5;
            ll cc=fa[i].y+0.5;
            res[i]=(aa+((bb%m)<<15)+((cc%m)<<30))%m;
        }
        return res;
    }
    vector<int> square_mod(vector<int> &a,int m)
    {
        return multiply_mod(a,a,m,1);
    }
};

int dp[MAXN],fact[MAXN],invf[MAXN];
inline int comb(int n,int k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}

int f[MAXN][25];

int pw[MAXN];
vector<int> pl, pr, ret;

inline void cdq(int l, int r) {
    if(l == r) {
        return;
    }
    int mid = l + r >> 1;
    cdq(l, mid);
    for (int t = 0; t <= 20; t += 1) {
        pl.clear();
        pr.clear();
        for (int i = l; i <= mid; i += 1) {
            pl.emplace_back(1ll * f[i][t] * invf[i] % MOD);
        }
        pr.emplace_back(0);
        for (int i = l + 1; i <= mid + 2; i += 1) {
            pr.emplace_back(1ll * dp[i - l] * invf[i - l - 1] % MOD);
        }
        ret = fft::multiply_mod(pl, pr, MOD);
        for (int i = mid + 1 - l; i <= r - l; i += 1) {
            add(f[i + l][t], 1ll * ret[i] * fact[i + l - 1] % MOD);
        }

        pr.clear();
        pr.emplace_back(0);
        for (int i = l + 1; i <= mid + 2; i += 1) {
            pr.emplace_back(1ll * pw[i - l] * invf[i - l - 1] % MOD);
        } 
        ret = fft::multiply_mod(pl, pr, MOD);
        for (int i = mid + 1 - l; i <= r - l; i += 1) {
            int tmp = 1ll * ret[i] * fact[i + l - 1] % MOD;
            for (int nt = t + 1; nt <= 20; nt += 1) {
                add(f[i + l][nt], 1ll * tmp * invf[nt - t] % MOD);
            }
        }
    }
    cdq(mid + 1, r);
}

int T;
int n, k;
int fuck[MAXN];

int main()
{
    fact[0]=invf[0]=1;
    pw[0] = pw[1] = 1;
    for (int i = 1; i <= 10000; i += 1) {
        fuck[i] = pow_mod(2, 1ll * i * (i - 1) / 2 % (MOD - 1));
    }
    for(int i=2;i<=50000;i++) pw[i] = pow_mod(i, i - 2);
    for(int i=1;i<=50000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[50000]=pow_mod(fact[50000],MOD-2);
    for(int i=49999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    dp[0]=1;
    for(int i=1;i<=10000;i++)
    {
        dp[i]=pow_mod(2,(1ll*i*(i-1)/2)%(MOD-1));
        for(int j=1;j<=i-1;j++) dec(dp[i],1LL*comb(i-1,j-1)*dp[j]%MOD*fuck[i-j]%MOD);
    }
    f[0][0] = 1;
    cdq(0, 10000);
    cin >> T;
    while(T--) {
        cin >> n >> k;
        cout << 1ll * f[n][k] * fact[k] % MOD << "\n";
    }
    return 0;
}
