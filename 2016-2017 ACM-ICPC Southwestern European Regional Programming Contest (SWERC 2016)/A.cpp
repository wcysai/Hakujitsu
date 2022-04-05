// #pragma comment(linker, "/STACK:102400000,102400000")
#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
// #pragma GCC optimize("trapv")
#include<bits/stdc++.h>
 
#define int long long
#define double long double
using namespace std;
 
 
// namespace std {
 
// template<class Fun>
// class y_combinator_result {
// 	Fun fun_;
// public:
// 	template<class T>
// 	explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
 
// 	template<class ...Args>
// 	decltype(auto) operator()(Args &&...args) {
// 		return fun_(std::ref(*this), std::forward<Args>(args)...);
// 	}
// };
 
// template<class Fun>
// decltype(auto) y_combinator(Fun &&fun) {
// 	return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
// }
 
// } // namespace std
 
#define rep(i,n) for (int i=0;i<(int)(n);++i)
#define rep1(i,n) for (int i=1;i<=(int)(n);++i)
#define range(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
 
typedef long long ll;
typedef unsigned long long ull;
// typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
 
int dx[]={0,1,0,-1,1,-1};
int dy[]={1,0,-1,0,1,-1};
// const int mod=998244353;
const int INF=INT_MIN;
const double EPS=1e-9;
const int N=27;
const int K=15;
 
mt19937 rng(1234);
 
int n;
double le[N],ri[N],a[N];
 
 
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
 
typedef Point<double> P;
 
vector<P> res;
bool circleInter(P a,P b,double r1,double r2,pair<P, P>* out) {
    // cerr<<a.x<<" "<<a.y<<" "<<b.x<<" "<<b.y<<" "<<r1<<" "<<r2<<endl;
	if (abs(a.x-a.y)<EPS&&abs(b.x-b.y)<EPS) {if (abs(r1-r2)<EPS){*out = {P(a.x+r1,a.y),P(a.x-r1,a.y)}; return true;} return false; }
	P vec = b - a;
	double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
	       p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2-EPS || dif*dif > d2+EPS) return false;
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid + per, mid - per};
	return true;
}
 
void solve(double d,int cur){
    // cerr<<d<<" "<<cur<<endl;
    if (cur==0) {
        res.pb(P(0,0));
        return;
    }
    assert(d<=ri[cur]+EPS&&d>=le[cur]-EPS);
    double to=min((double)ri[cur-1],d+a[cur]);
    solve(to,cur-1);
    auto ret=res.back();
    P c1(0,0), c2(ret);
    pair<P,P> tmp;
    circleInter(c1,c2,d,a[cur],&tmp);
    res.pb(tmp.F);
}
signed main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cout.precision(15), cerr.precision(15);
    cin>>n;
    rep1(i,n) cin>>a[i];
    rep1(i,n){
        if (a[i]>=le[i-1]&&a[i]<=ri[i-1]) le[i]=0;
        else le[i]=min(max(a[i]-le[i-1],le[i-1]-a[i]),max(a[i]-ri[i-1],ri[i-1]-a[i]));
        ri[i]=ri[i-1]+a[i];
    }
    int x,y;
    cin>>x>>y;
    if(x==0&&y==0) y=1;
    P pp(x,y);
    if (pp.dist()<le[n]) pp=pp.unit()*le[n];
    if (pp.dist()>ri[n]) pp=pp.unit()*ri[n];
    solve(pp.dist(),n);
    auto ret=res.back();
    double ang=pp.angle()-ret.angle();
    for (auto &c:res) c=c.rotate(ang);
    rep1(i,sz(res)-1){
        auto c=res[i];
        cout<<c.x<<" "<<c.y<<"\n";
    } 
    return 0;
}
 
/*
5
-7 -7
-11 -10
-8 -5
-1 -1
-12 -12
*/