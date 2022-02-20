#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define double long double
using namespace std;
typedef long long ll;
typedef pair<double,double> P;
int n,k;
int sz;
const double eps=1e-9;
vector<vector<double> > mat;
vector<double> ans;
bool IsZero(double v) 
{
    return abs(v)<eps;
}
enum GAUSS_MODE {
  DEGREE, ABS
};
template <typename T>
void GaussianElimination(vector<vector<T>>&a, int limit, GAUSS_MODE mode=ABS) 
{
    if(a.empty()||a[0].empty()) return;
    int h=static_cast<int>(a.size());
    int w=static_cast<int>(a[0].size());
    vector<int> deg(h);
    for(int i=0;i<h;i++) 
        for(int j=0;j<w;j++) 
            deg[i]+=!IsZero(a[i][j]);
    int r=0;
    for(int c=0;c<limit;c++) 
    {
        int id=-1;
        for(int i=r;i<h;i++) 
            if(!IsZero(a[i][c])&&(id==-1||(mode==DEGREE&&deg[i]<deg[id])||(mode==ABS&&abs(a[id][c])<abs(a[i][c]))))
                id=i;
        if(id==-1) continue;
        if(id>r) 
        {
            swap(a[r],a[id]); swap(deg[r],deg[id]);
            for(int j=c;j<w;j++) a[id][j]=-a[id][j];
        }
        vector<int> nonzero;
        for(int j=c;j<w;j++) 
            if(!IsZero(a[r][j])) 
                nonzero.push_back(j);
        T inv_a=1/a[r][c];
        for(int i=r+1;i<h;i++) 
        {
            if(IsZero(a[i][c])) 
                continue;
            T coeff=-a[i][c]*inv_a;
            for (int j:nonzero) 
            {
                if (!IsZero(a[i][j])) deg[i]--;
                a[i][j] += coeff * a[r][j];
                if (!IsZero(a[i][j])) deg[i]++;
            }
        }
        ++r;
    }
    for(r=h-1;r>=0;r--) 
    {
        for(int c=0;c<limit;c++) 
        {
            if(!IsZero(a[r][c])) 
            {
                T inv_a=1/a[r][c];
                for(int i=r-1;i>=0;i--) 
                {if (IsZero(a[i][c])) {
            continue;
          }
          T coeff = -a[i][c] * inv_a;
          for (int j = c; j < w; j++) {
            a[i][j] += coeff * a[r][j];
          }
        }
        break;
      }
    }
  }
}
 
template <typename T>
vector<T> SolveLinearSystem(vector<vector<T>> a, const vector<T>& b, int w) {
  int h = static_cast<int>(a.size());
  assert(h == static_cast<int>(b.size()));
  if (h > 0) {
    assert(w == static_cast<int>(a[0].size()));
  }
  for (int i = 0; i < h; i++) {
    a[i].push_back(b[i]);
  }
  GaussianElimination(a, w);
  vector<T> x(w, 0);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (!IsZero(a[i][j])) {
        x[j] = a[i][w] / a[i][j];
        break;
      }
    }
  }
  return x;
}
double prob;
double p[10],np[10];
int main()
{
	scanf("%d%d%Lf",&n,&k,&prob);
	p[0]=np[0]=1.0;
	for(int i=1;i<=n;i++) p[i]=p[i-1]*prob;
	for(int i=1;i<=n;i++) np[i]=np[i-1]*(1.0-prob);
	mat.resize(1<<n); ans.resize(1<<n);
	for(int i=0;i<(1<<n);i++) mat[i].resize(1<<n);
	int all=(1<<n)-1;
	for(int mask=0;mask<(1<<n);mask++)
	{
		for(int j=0;j<(1<<n);j++) mat[mask][j]=0.0;
		if(__builtin_popcount(mask)==k) 
		{
			mat[mask][mask]=1.0;
			ans[mask]=0.0;
		}
		else
		{
			int xmask=((mask<<1)|1)&all;
			int ymask=(mask<<1)&all;
			mat[mask][mask]=1.0;
			mat[mask][xmask]-=prob;
			mat[mask][ymask]-=(1.0-prob);
			ans[mask]=1.0;
		}
	}
	auto res=SolveLinearSystem(mat,ans,(1<<n));
	for(int mask=0;mask<(1<<n);mask++)
	{
		double tmp=0.0;
		for(int j=0;j<(1<<n);j++) tmp+=res[j]*mat[mask][j];
	}
	double ret=0.0;
	for(int mask=0;mask<(1<<n);mask++)
	{
		int cnt=__builtin_popcount(mask);
		int last=-1,tot=0;
		for(int j=0;j<n;j++)
		{
			if(mask&(1<<j)) tot++;
			if(tot==k) {last=j+1; break;}
		}
		if(last==-1) ret+=(n+res[mask])*p[cnt]*np[n-cnt]; else ret+=1.0*last*p[cnt]*np[n-cnt];
	}
	printf("%.15Lf\n",ret);
	return 0;
}