#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
double prob[105][6];
int num[MAXN][5];
double pr[MAXN],spr[MAXN];
int n;
mt19937 wcy(time(NULL));
bool check_distinct(int i,int j)
{
    set<int> s;
    for(int k=0;k<5;k++) s.insert(num[i][k]);
    for(int k=0;k<5;k++) s.insert(num[j][k]);
    return s.size()==10;
}
double get_ans(int i,int j)
{
    double ans=0.0;
    int mini=num[i][0],minj=num[j][0];
    if(mini<minj)
    {
        for(int ii=0;ii<5;ii++)
            for(int jj=ii+1;jj<=5;jj++)
                ans+=prob[mini][ii]*prob[minj][jj];
    }
    else
    {
        ans=1.0;
        for(int ii=0;ii<5;ii++)
            for(int jj=ii+1;jj<=5;jj++)
                ans-=prob[mini][ii]*prob[minj][jj];
    }
    return ans;
}
double gen_test()
{
    for(int i=1;i<=1000;i++)
    {
        set<int> s;
        for(int j=0;j<5;j++)
        {
            int x=wcy()%100+1;
            while(s.count(x)) x=wcy()%100+1;
            s.insert(x);
        }
        int tot=0;
        for(auto x:s) num[i][tot++]=x;
    }
    double res=0.0;
    int cnt=0;
    for(int i=1;i<=1000;i++)
        for(int j=i+1;j<=1000;j++)
        {
            if(!check_distinct(i,j)) continue;
            cnt++;
            res+=get_ans(i,j);
        }
    return res/cnt;
}
int main()
{
    for(int i=1;i<=100;i++) 
    {
        pr[i]=powl((double)(101-i)/100.0,5)-powl((double)(100-i)/100.0,5);
        spr[i]=spr[i-1]+pr[i];
    }
    for(int i=1;i<=100;i++)
    {
        int sector=floor((spr[i]-0.00001)*6);
        prob[i][sector]=1.0;
    }
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int a[5];
        for(int j=0;j<5;j++) scanf("%d",&a[j]);
        for(int j=0;j<5;j++) printf("%.10f ",prob[a[0]][j]);
        printf("\n");
        fflush(stdout);
    }
    return 0;
}