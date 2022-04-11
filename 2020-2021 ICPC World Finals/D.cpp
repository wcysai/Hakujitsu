#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 8000005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void manacher(char str[],int len[],int n)
{
    len[0]=1;
    for(int i=1,j=0;i<(n<<1)-1;++i)
    {
        int p=i>>1,q=i-p,r=((j+1)>>1)+len[j]-1;
        len[i]=r<q?0:min(r-q+1,len[(j<<1)-i]);
        while(p>len[i]-1&&q+len[i]<n&&str[p-len[i]]==str[q+len[i]])
            ++len[i];
        if(q+len[i]-1>r)
            j=i;
    }
}
int a[MAXN];
char str[MAXN];
int main()
{
    scanf("%s",str);
    int n=strlen(str);
    manacher(str,a,strlen(str));
    int l=0,r=n-1;
    for(int i=1;i<2*n-1;i+=2)
    {
    	int pre=(i/2+1-l);
    	int suf=n-1-(i/2);
    	if(pre<=0||suf<=0) continue;
    	if(pre>suf) break;
    	if(a[i]>=pre) l+=pre;
    }
    for(int i=2*n-3;i>=0;i-=2)
    {
    	int suf=r-(i/2);
    	int pre=(i/2+1-l);
    	if(pre<=0||suf<=0) continue;
    	if(pre<suf) continue;
    	if(a[i]>=suf) r-=suf;
    }
    printf("%d\n",r-l+1);
    return 0;
}