#include <bits/stdc++.h>

using namespace std;

const int N=1e5+10;
int id,n,x,y,vis[N],sum,mn=N,w[N],fa[N],ad,T,ty;
vector <int > v[N];

void cl(int nw,int fa,vector <int > &pl)
{
	int flag=0;
	for(int go:v[nw]) if(go!=fa&&w[go]==0&&vis[go]==0)
	{
		cl(go,nw,pl);
		flag=1;
	}
	if(flag==0) vis[nw]=1,ad++,pl.push_back(nw);
	return ;
}

void solve(int st,int cnt) 
{
	if(st>mn) return ;
	if(cnt==0)
	{
		if(mn==st) sum++; 
		if(st<mn) mn=st,sum=1;
		return ;
	}
	for(int i=1;i<=n;i++) 
	{
		w[i]=1;
		ad=0;
		vector <int > pl;
		cl(i,fa[i],pl);
		if(ad) solve(st+1,cnt-ad);
		for(int k:pl) vis[k]=0;
		w[i]=0;
	}
	return ;
}

void dfs(int nw,int af)
{
	fa[nw]=af;
	for(int go:v[nw]) if(go!=af) dfs(go,nw);
	return ;
}

int main()
{
	freopen("recall.in","r",stdin);
	freopen("recall.out","w",stdout);
	scanf("%d%d",&ty,&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<n;i++) 
		{
			scanf("%d%d",&x,&y);
			v[x].push_back(y);
			v[y].push_back(x);
		}
		if(ty==2)
		{
			printf("%d 2\n",n);
		}
		else if(ty==3)
		{
			if(n>2) printf("2 1\n");
			else if(n==2) printf("2 2\n");
			else printf("1 1");
		}
		else
		{
			w[1]=1;
			dfs(1,0);
			solve(0,n); 
			printf("%d %d\n",mn,sum);
		}
		for(int i=1;i<=n;i++) vis[i]=0,v[i].clear(),w[i]=fa[i]=0;
		mn=N,sum=0;
	}
	return 0; 
} 
