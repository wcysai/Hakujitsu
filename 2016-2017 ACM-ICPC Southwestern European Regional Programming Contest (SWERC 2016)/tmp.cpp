#include<stdio.h>
#include <math.h>
using namespace std;
int fac[10],a[10];
#define db  double
db p[10],f[10];
int n,m;
void dfs(int now,int remain) 
{
    if(now==m)
    {
        a[now]=remain; //dfs出
        int tmp=fac[n-1];
        for(int i=1;i<=m;i++)tmp/=fac[a[i]];
        db poss=tmp;
        for(int i=1;i<=m;i++) poss*=pow(p[i],a[i]); //n-1个人发生给定A的选数情况下的概率是 ∏pi^ai * (n-1)! /(∏ai!)
        for(int i=1;i<=m;i++)
        {
            if(!a[i])
            f[i]+=poss;
            else if(a[i]==1)break;
        }
        return ;
    }
    for(int i=0;i<=remain;i++)
    {
        a[now]=i;
        dfs(now+1,remain-i);
    }
}
bool check()
{
    int mx=1;
    for(int i=1;i<=m;i++)
        if(f[i]>f[mx])mx=i;
    for(int i=1;i<=m;i++)
        if(fabs(f[i]-f[mx])>1e-6)return false;
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    fac[0]=1;
    for(int i=1;i<10;i++)   fac[i]=fac[i-1]*i;
    for(int i=1;i<=m;i++)   p[i]=1./m;
    db o=10;
    do
    {
        for(int i=1;i<=m;i++) f[i]=0;
        dfs(1,n-1);
        o*=1.001;
        for(int i=1;i<=m;i++)
        printf("%.5f ",(double)f[i]);
        puts("");
        for(int i=1;i<m;i++)
        {
            p[i]+=(f[i]-f[i+1])/o,p[i+1]-=(f[i]-f[i+1])/o;
        }

    
    }while(!check());
    for(int i=1;i<=m;i++)
        printf("%.5f\n",(double)p[i]);
    return 0;
}