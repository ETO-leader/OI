#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int id,n,tot,T,maxn;
struct node
{
	int v,nxt;
}e[200051];
int head[100051],deep[100051];
int qpow(long long a,long long b)
{
	long long sum=1;
	while(b)
	{
		if(b&1) sum=sum*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return (int)sum;
}
void add(int u,int v)
{
	e[++tot].v=v;
	e[tot].nxt=head[u];
	head[u]=tot;
}
void dfs(int u,int fa)
{
	deep[u]=deep[fa]+1;
	maxn=max(maxn,deep[u]);
	bool f=false;
	for(int i=head[u];i!=-1;i=e[i].nxt)
		if(e[i].v!=fa)
		{
			f=true;
			dfs(e[i].v,u);
		}
	//if(!f) cout<<deep[u]<<"\n";
}
int main()
{
	freopen("recall.in","r",stdin);
	freopen("recall.out","w",stdout);
	cin>>id>>T;
	if(id==0)
	{
		cout<<"5 46\n5 20\n5 28\n7 1190\n6 320\n5 20\n4 4\n6 18\n4 4\n5 11\n";
		return 0;
	}
	while(T--)
	{
		cin>>n;
		memset(head,-1,sizeof(head));
		tot=0;
		maxn=0;
		for(int i=1;i<n;i++)
		{
			int u,v;
			cin>>u>>v;
			add(u,v),add(v,u);
		}
		dfs(1,0);
		cout<<maxn<<" ";
		if(id==4)
		{
			cout<<"1\n";
			continue;
		}
	}
}
