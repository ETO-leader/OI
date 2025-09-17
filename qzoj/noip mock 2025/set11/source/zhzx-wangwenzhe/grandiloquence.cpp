#include<bits/stdc++.h>
using namespace std;
int n,id,m,tot,x,c,tt,k,ans,pre;
int fa[100051],co[100051];
struct node
{
	int v,nxt;
}e[1000051];
int head[1000051];
void add(int u,int v)
{
	e[++tot].v=v;
	e[tot].nxt=head[u];
	head[u]=tot;
}
void dfs1(int u,int dis)
{
	co[u]=(dis+c-1)%k+1;
	for(int i=head[u];i!=-1;i=e[i].nxt)
		dfs1(e[i].v,dis+1);
}
void dfs2(int u)
{
	if(co[u]==c) ans++;
	for(int i=head[u];i!=-1;i=e[i].nxt)
		dfs2(e[i].v);
}
int main()
{
	freopen("grandiloquence.in","r",stdin);
	freopen("grandiloquence.out","w",stdout);
	cin>>id;
	cin>>n>>m>>k;
	memset(head,-1,sizeof(head));
	for(int i=1;i<=n;i++)
		cin>>fa[i],add(fa[i],i);
	tt=n;
	while(m--)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			cin>>x>>c;
			if(id%2==0) x^=pre,c^=pre;
			dfs1(x,0);
		}
		else if(op==2)
		{
			cin>>x>>c;
			if(id%2==0) x^=pre,c^=pre;
			ans=0;
			dfs2(x);
			pre=ans;
			cout<<ans<<"\n";
		}
		else
		{
			cin>>x;
			if(id%2==0) x^=pre;
			tt++;
			add(x,tt);
		}
	}
}
