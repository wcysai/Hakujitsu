#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
const db eps=1e-10;
struct num
{
    db x,y;
    num() {x=y=0;}
    num(db x,db y):x(x),y(y){}
};
bool eq(db x,db y)
{
    return max(x-y,y-x)<eps;
}
inline num operator+(num a,num b) {return num(a.x+b.x,a.y+b.y);}
inline num operator-(num a,num b) {return num(a.x-b.x,a.y-b.y);}
inline num operator*(num a,num b) {return num(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
inline db norm2(num a) {return a.x*a.x+a.y*a.y;}
inline num conj(num a) {return num(a.x,-a.y);}
inline num operator/(num a,db b) {return num(a.x/b,a.y/b);}
inline num operator/(num a,num b) {return (a*conj(b))/norm2(b);}
inline bool operator==(num a,num b) {return eq(a.x,b.x)&&eq(a.y,b.y);}
int T;
num z0,z1,z2,z3,w1,w2,w3;
void read(num &x)
{
    db a,b;
    scanf("%Lf%Lf",&a,&b);
    x=num(a,b);
}
void print(num &x)
{
    printf("%.10Lf %.10Lf\n",x.x,x.y);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        read(z1); read(w1); read(z2); read(w2); read(z3); read(w3); read(z0);
        //c==0,az+b=w
        num a,b,c,d,res;
        a=(w2-w1)/(z2-z1);
        b=w1-(a*z1);
        if(a*z3+b==w3)
        {
            res=a*z0+b;
            print(res); continue;
        }
        num d12z=z1-z2,d13z=z1-z3;
        num d12w=w1-w2,d13w=w1-w3;
        num d12zw=(z1*w1-z2*w2),d13zw=(z1*w1-z3*w3);
        c=((d12zw*d13z)-(d13zw*d12z))/(d12z*d13w-d13z*d12w);
        b=(d12zw+c*d12w)/d12z;
        a=(w1-b)*(z1+c);
        res=a/(z0+c)+b;
        print(res); 
    }
    return 0;
}