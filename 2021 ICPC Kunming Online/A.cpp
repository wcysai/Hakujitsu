#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int m,n,cnt;
map<string,int> mp;
int wt[10]={89,132,133,121,146,147,75,149,105,119};
string str[10][10];
int sz[10]={4,5,4,4,6,5,3,7,4,5};
bool valid[10];
int cur,maxi;
bool has;
string ans[20];
vector<int> amino;
void add(int id,bool pre,bool suf)
{
	if(!pre)
	{
		for(int i=0;i<2*maxi-1;i++)
		{
			if(i==2) {ans[i]+='H'; ans[i]+='-';}
			else {ans[i]+=' '; ans[i]+=' ';} 
		}
	}
	for(int i=0;i<maxi;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(j==3)
			{
				if(i==1)
				{
					if(suf) ans[2*i]+="--"; else ans[2*i]+="O-H";
					if(suf) ans[2*i-1]+="  "; else ans[2*i-1]+="   ";
				}
				else 
				{
					if(str[id][i][j]=='.') ans[2*i]+=' '; else ans[2*i]+=str[id][i][j];
					if(i>0) ans[2*i-1]+=' ';
					ans[2*i]+=' '; if(i>0) ans[2*i-1]+=' ';
					if(!suf) 
					{
						ans[2*i]+=' '; if(i>0) ans[2*i-1]+=' ';
					}
				}
			}
			else
			{
				if(str[id][i][j]=='.') {ans[2*i]+="  ";}
				else
				{
					ans[2*i]+=str[id][i][j];
					if(j==3||str[id][i][j+1]=='.') ans[2*i]+=' ';
					else 
					{
						if(str[id][i][j]=='O'&&str[id][i][j+1]=='C') ans[2*i]+='=';
						else 
						{
							if(i!=0) ans[2*i]+='-'; else ans[2*i]+=' ';
						}
					}
				}
				if(i>0)
				{
					if(str[id][i][j]=='.'||str[id][i-1][j]=='.') {ans[2*i-1]+="  ";}
					else 
					{
						if(str[id][i][j]=='C'&&str[id][i-1][j]=='O') {ans[2*i-1]+="||";}
						else 
						{
							if(j==1||i==1||(id==1&&i==4&&j==2)||(id==4&&i==5&&j==2)){ans[2*i-1]+="| ";}
							else  ans[2*i-1]+="  ";
						}
					}
				}
			}
		}
	}
}
void clear()
{
	for(int i=0;i<=2*maxi-1;i++) ans[i]="";
}
void print()
{
	clear();
	maxi=0;
	for(auto x:amino) maxi=max(maxi,sz[x]);

	for(int i=0;i<(int)amino.size();i++)
		add(amino[i],(i>0),(i<(int)amino.size()-1));
	if(has) cout<<endl;
	//for(auto x:amino) printf("%d ",x);
	//puts("");
	//printf("maxi=%d\n",maxi);
	for(int i=0;i<2*maxi-1;i++) cout<<ans[i]<<endl;
	has=true;
}
void dfs(int sum,int num,bool pr=false)
{
	if(num>1)
	{
		cnt++;
		if(pr) print();
	}
	for(int i=0;i<10;i++)
	{
		if(valid[i]&&sum+(sum==0?wt[i]:wt[i]-18)<=n)
		{
			amino.push_back(i);
			dfs(sum+(sum==0?wt[i]:wt[i]-18),num+1,pr);
			amino.pop_back();
		}
	}
}
string tmp;
int main()
{
	for(int i=0;i<10;i++) for(int j=0;j<10;j++) str[i][j]="....";
	mp["Ala"]=0; mp["Asp"]=2; mp["Asn"]=1; mp["Cys"]=3; mp["Gly"]=6;
	mp["Ser"]=8; mp["Met"]=7; mp["Thr"]=9; mp["Gln"]=4; mp["Glu"]=5;
	for(int i=0;i<10;i++) {str[i][0]="HHO."; str[i][1]="NCCO"; str[i][2]="HCH.";}
	str[0][3]=".H..";
	str[2][3]="OCOH";
	str[1][3]="OCNH"; str[1][4]="..H.";
	str[3][2]="HCSH"; str[3][3]=".H..";
	str[6][2]=".H..";
	str[8][2]="HCOH"; str[8][3]=".H..";
	str[7][3]="HCH."; str[7][4]=".S.."; str[7][5]="HCH."; str[7][6]=".H..";
	str[9][2]="HCOH"; str[9][3]="HCH."; str[9][4]=".H..";
 	str[4][3]="HCH."; str[4][4]="OCNH"; str[4][5]="..H.";
 	str[5][3]="HCH."; str[5][4]="OCOH";
 	memset(valid,false,sizeof(valid)); 
 	scanf("%d%d",&m,&n);
 	for(int i=0;i<m;i++)
 	{
 		cin>>tmp;
 		valid[mp[tmp]]=true;
 	}
 	dfs(0,0);
 	printf("%d\n",cnt);
 	dfs(0,0,true);
	return 0;
}