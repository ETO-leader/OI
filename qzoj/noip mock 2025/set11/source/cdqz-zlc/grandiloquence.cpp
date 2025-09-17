#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
inline int read()
{
	int x=0,fu=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fu=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*fu;
}
void write(int x)
{
	if(x<0)	x=-x,putchar('-');
	if(x<10){putchar(x+'0');return;}
	write(x/10);putchar(x%10+'0');
}

const int N=1e4+10;
bool tp;
int n,m,k,ans,res;
int col[N];
vector<int>ed[N];
void dfs(int u,int c,int dis)
{
	col[u]=(dis+c-1)%k+1;
	for(int v:ed[u])
	{
		dfs(v,c,dis+1);
	}
}
void query(int u,int c)
{
	if(col[u]==c)	res++;
//	if(!m)	cout<<u<<" "<<col[u]<<endl;
	for(int v:ed[u])
	{
		query(v,c);
	}
}
signed main()
{
	freopen("grandiloquence.in","r",stdin);
	freopen("grandiloquence.out","w",stdout);
	tp=read();
	n=read(),m=read(),k=read();
	col[1]=-1;
	for(int i=1;i<=n;i++)
	{
		int x=read();
		col[x]=-1;
		ed[x].push_back(i);
	}
	while(m--)
	{
		int op=read();
		if(op==1)
		{
			int u=read(),c=read();
			if(tp)	u^=ans,c^=ans;
			dfs(u,c,0);
		}
		if(op==2)
		{
			int u=read(),c=read();
			if(tp)	u^=ans,c^=ans;
			res=0;
			query(u,c);
			write(res),puts("");
			ans=res;
		}
		if(op==3)
		{
			int u=read();
			if(tp)	u^=ans;
			ed[u].push_back(++n);
			col[n]=-1;
		}
	}
	return 0;
}

