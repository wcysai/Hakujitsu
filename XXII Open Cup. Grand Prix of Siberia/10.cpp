#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 2048
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,x,y;
char s[MAXN][MAXN],t[MAXN][MAXN];
int a[MAXN][MAXN],b[MAXN][MAXN],c[MAXN][MAXN];
const int g=3; 
int two[31];
int dbit(int x)
{
    while(x!=(x&-x)) x+=(x&-x);
    return x;
}
int pow_mod(int a,int i)
{
    if(i==0) return 1;
    int s=1;
    while(i>0)
     {
         if(i&1) s=(1LL*s*a)%MOD;
         a=(1LL*a*a)%MOD;
         i>>=1;
     }
     return s;
}
int rev(int x,int r)  
{  
    int ans=0;  
    for(int i=0;i<r;i++)  
        if(x&(1<<i)) ans+=1<<(r-i-1);   
    return ans;  
}  
void ntt(int n,int A[],int on)
{
    int r=0,cnt=0,t=n; 
    while(t>1) {cnt++; t/=2;} 
    for(;;r++) if((1<<r)==n)  break;   
    for(int i=0;i<n;i++)  
    {  
        int tmp=rev(i,r);  
        if(i<tmp) swap(A[i],A[tmp]);  
    }  
    for(int s=1;s<=r;s++)  
    {  
        int m=1<<s;  
        int wn=pow_mod(g,(MOD-1)/m);  
        for(int k=0;k<n;k+=m)  
        {  
            int w=1;  
            for(int j=0;j<m/2;j++)  
            {  
                int t,u;  
                t=1LL*w*A[k+j+m/2]%MOD;  
                u=A[k+j];  
                A[k+j]=(u+t);
                if(A[k+j]>=MOD) A[k+j]-=MOD;  
                A[k+j+m/2]=u+MOD-t;
                if(A[k+j+m/2]>=MOD) A[k+j+m/2]-=MOD;
                w=1LL*w*wn%MOD;  
            }  
        }  
    }  
    if(on==-1)  
    {  
        for(int i=1;i<n/2;i++)  
            swap(A[i],A[n-i]);    
        for(int i=0;i<n;i++)  
            A[i]=1LL*A[i]*two[cnt]%MOD;  
    }  
}
void transpose(int a[][MAXN])
{
	for(int i=0;i<2048;i++)
		for(int j=i+1;j<2048;j++)
			swap(a[i][j],a[j][i]);
}
void two_d_fft()
{
	for(int i=0;i<2048;i++) ntt(2048,a[i],1),ntt(2048,b[i],i);
	transpose(a); transpose(b);
	for(int i=0;i<2048;i++) ntt(2048,a[i],1),ntt(2048,b[i],1);
	for(int i=0;i<2048;i++)
		for(int j=0;j<2048;j++)
			a[i][j]=1LL*a[i][j]*b[i][j]%MOD;
	for(int i=0;i<2048;i++) ntt(2048,a[i],-1);
	transpose(a);
	for(int i=0;i<2048;i++) ntt(2048,a[i],-1);
}
vector<P> v;
int main()
{
	for(int i=1;i<=30;i++) two[i]=pow_mod(1<<i,MOD-2); 
	scanf("%d%d%d%d",&n,&m,&x,&y);
	for(int i=0;i<n;i++) cin>>s[i];
	for(int i=0;i<x;i++) cin>>t[i];
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(s[i][j]=='#') a[i][j]=1;
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
			if(t[i][j]=='.') b[x-1-i][y-1-j]=1;
	two_d_fft();
	for(int i=0;i<2048;i++)
		for(int j=0;j<2048;j++)
			c[i][j]+=a[i][j];
	memset(a,0,sizeof(a)); memset(b,0,sizeof(b));
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(s[i][j]=='.') a[i][j]=1;
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
			if(t[i][j]=='#') b[x-1-i][y-1-j]=1;
	two_d_fft();
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			c[i][j]+=a[i][j];
	for(int i=0;i<=n-x;i++)
		for(int j=0;j<=m-y;j++)
			if(!c[x-1+i][y-1+j]) v.push_back(P(i+1,j+1));
	printf("%d\n",(int)v.size());
	for(auto p:v) printf("%d %d\n",p.F,p.S);
	return 0;
}