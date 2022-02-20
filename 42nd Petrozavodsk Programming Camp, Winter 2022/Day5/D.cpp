#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
typedef long double db;
int t,n,m;
vector<P> blue,yellow;
const db eps=1e-8;
db calc(db x,db y)
{
    db xres=-1e18,yres=1e18;
    for(auto p:yellow) xres=max(xres,sqrt(1.0*(p.F-x)*(p.F-x)+1.0*(p.S-y)*(p.S-y)));
    for(auto p:blue) yres=min(yres,sqrt(1.0*(p.F-x)*(p.F-x)+1.0*(p.S-y)*(p.S-y)));
    return yres-xres;
}
pair<db,db> calc_y(db x)
{
    db l=-1e9,r=1e9;
    for(int i=0;i<60;i++)
    {
        double lmid=l+(r-l)/3.0,rmid=r-(r-l)/3.0;
        if(calc(x,lmid)>calc(x,rmid)) r=rmid; else l=lmid;
    }
    return make_pair(calc(x,l),l);
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		blue.clear(); yellow.clear();
		for(int i=0;i<n;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			blue.push_back(P(x,y));
		}
		scanf("%d",&m);
		for(int i=0;i<m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			yellow.push_back(P(x,y));
		}
		db l=-1e9,r=1e9;
		for(int i=0;i<60;i++)
	    {
	        db lmid=l+(r-l)/3.0,rmid=r-(r-l)/3.0;
	        if(calc_y(lmid)>calc_y(rmid)) r=rmid; else l=lmid;
	        printf("%.10Lf %.10Lf %.10Lf %.10Lf %.10Lf %.10Lf\n",l,r,lmid,rmid,calc_y(lmid).F,calc_y(rmid).F);
	    }

	    db x=l,y=calc_y(l).S;

		printf("%.15Lf %.15Lf\n",x,y);
		printf("%.15Lf\n",calc(x,y));
	    assert(calc(x,y)>=0);
	    db rad=-2e9;
	    for(auto p:yellow) rad=max(rad,sqrt(1.0*(p.F-x)*(p.F-x)+1.0*(p.S-y)*(p.S-y)));
	    printf("%.15Lf\n",rad);
		printf("%.15Lf %.15Lf\n",x,y);
	}
	return 0;
}