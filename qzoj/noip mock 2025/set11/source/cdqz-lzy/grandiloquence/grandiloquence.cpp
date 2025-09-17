#include <bits/stdc++.h>

using namespace std;

const int N=2e4+10;
int t,n,m,k,tot,x,lst,u,fa[N],col[N],cnt,op;
vector <int > v[N];

void dfs(int nw,int fa,int st)
{
	col[nw]=(st+x-1)%k+1;
	for(int go:v[nw]) if(go!=fa) 
	{
		dfs(go,nw,st+1);
	}
	return ;
}

void find(int nw,int fa,int st)
{
	if(col[nw]==st) cnt++;
	for(int go:v[nw]) if(go!=fa) 
	{
		find(go,nw,st);
	}
	return ;
}

int main()
{
	freopen("grandiloquence.in","r",stdin);
	freopen("grandiloquence.out","w",stdout);
	scanf("%d%d%d%d",&t,&n,&m,&k);
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&fa[i]);
		if(fa[i]) v[fa[i]].push_back(i);
	}
	tot=n;
	while(m--) 
	{
		scanf("%d%d",&op,&u);
		if(t==1) u^=lst;
		if(op==1) 
		{
			scanf("%d",&x);
			if(t==1) x^=lst;
			dfs(u,fa[u],0);
		}
		else if(op==2) 
		{
			scanf("%d",&x);
			if(t==1) x^=lst;
			cnt=0;
			find(u,fa[u],x);
			printf("%d\n",cnt);
		}
		else fa[++tot]=u,v[u].push_back(tot);
	}
	return 0;
} 
