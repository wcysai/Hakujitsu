#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
int n,q,tot;
ll k;
map<string,int> mp;
int get_id(string &str)
{
	if(mp.find(str)==mp.end()) mp[str]=++tot;
	return mp[str];
}
int cur[MAXN],cnt[MAXN],mxcnt[MAXN],maxi[MAXN],sum[MAXN];
string str;
int main()
{
	scanf("%d%lld",&n,&k);
	for(int i=0;i<n;i++)
	{
		cin>>str;
		int x;
		scanf("%d",&x);
		cur[get_id(str)]=x;
	}
	scanf("%d",&q);
	ll need=0,ans=0,s=0;
	bool f=true;
	for(int i=0;i<q;i++)
	{
		cin>>str;
		int x;
		scanf("%d",&x);
		int id=get_id(str);
		if(x>maxi[id]) mxcnt[id]=1; else if(x==maxi[id]) mxcnt[id]++; 
		maxi[id]=max(maxi[id],x);
		sum[id]+=x;
		cnt[id]++;
	}
	int maxnum=0;
	for(int i=1;i<=tot;i++)
	{
		if(maxi[i]>=cur[i])
		{
			k-=(maxi[i]-cur[i]);
			cur[i]=maxi[i];
			s+=1LL*cur[i]*(cnt[i]-mxcnt[i]);
		}
		else 
		{
			s+=1LL*cnt[i]*cur[i];
			maxnum=max(maxnum,cnt[i]);
		}
	}
	if(k<0) {puts("0"); return 0;}
	vector<pair<ll,int> > v;
	for(int i=1;i<=tot;i++)
		if(maxi[i]==cur[i]) v.push_back(make_pair(1LL*maxi[i]*mxcnt[i]+cnt[i],cnt[i]));
	sort(v.begin(),v.end());
	vector<ll> sum;
	sum.resize(v.size()+1);
	sum[v.size()]=0;
	for(int i=v.size()-1;i>=0;i--) sum[i]=sum[i+1]+v[i].F;
	//use curmaxnum
	int pos=lower_bound(v.begin(),v.end(),P(maxnum,INF))-v.begin();
	if(v.size()-pos<=k) ans=max(ans,s+sum[pos]+1LL*(k-((int)v.size()-pos))*maxnum);
	else ans=max(ans,s+sum[(int)v.size()-k]);
	for(int i=0;i<(int)v.size();i++)
	{
		int pos=lower_bound(v.begin(),v.end(),P(v[i].S,INF))-v.begin();
		if(pos>i&&v.size()-pos<=k-1) ans=max(ans,s+sum[pos]+1LL*(k-1-((int)v.size()-pos))*v[i].S+v[i].F);
		if(pos<=i&&v.size()-pos<=k) ans=max(ans,s+sum[pos]+1LL*(k-((int)v.size()-pos))*v[i].S);
	} 
	printf("%lld\n",ans);
	return 0;
}

