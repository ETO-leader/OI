#include<bits/stdc++.h>
#define F(i,l,r) for(int i=(l),i##end=(r);i<=i##end;++i)
#define G(i,l,r) for(int i=(l),i##end=(r);i>=i##end;--i)
#define pii pair<int,int>
#define x first
#define y second
#define mp(x,y) make_pair(x,y)
#define ep emplace_back
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N=2e5+9,B=10;
ll L[N],R[N];
vector<int> E[N];
int k;
struct node
{
	int dep[B],cnt[B],tag;
}tr[N<<3];
int fa[N],dfn[N],sz[N],dfntot;
int dep[N];
void dfs(int x)
{
	dep[x]=dep[fa[x]]+1;
	dfn[x]=++dfntot;
	sz[x]=1;
	for(auto u:E[x])dfs(u),sz[x]+=sz[u];
}
void pushdown(int o)
{
	if(tr[o].tag!=-1)
	{
		F(i,0,k-1)tr[o<<1].cnt[(i+tr[o].tag)%k]=tr[o<<1].dep[i];
		F(i,0,k-1)tr[o<<1|1].cnt[(i+tr[o].tag)%k]=tr[o<<1|1].dep[i];
		tr[o<<1].tag=tr[o<<1|1].tag=tr[o].tag;
		tr[o].tag=-1;
	}
}
void add(int l,int r,int o,int a,int b)
{
	if(l==r)return tr[o].dep[b%k]=1,void();
	int mid=l+r>>1;
	pushdown(o);
	if(a<=mid)add(l,mid,o<<1,a,b);
	if(a>mid) add(mid+1,r,o<<1|1,a,b);
	F(i,0,k-1)tr[o].dep[i]=tr[o<<1].dep[i]+tr[o<<1|1].dep[i];
	F(i,0,k-1)tr[o].dep[i]=tr[o<<1].cnt[i]+tr[o<<1|1].cnt[i];
}
void modify(int l,int r,int o,int a,int b,int c)
{
	if(a<=l && r<=b)
	{
		F(i,0,k-1)tr[o].cnt[(i+c)%k]=tr[o].dep[i];
		tr[o].tag=c;
		return ;
	}
	int mid=l+r>>1;
	pushdown(o);
	if(a<=mid)modify(l,mid,o<<1,a,b,c);
	if(b>mid)modify(mid+1,r,o<<1|1,a,b,c);
	F(i,0,k-1)tr[o].dep[i]=tr[o<<1].dep[i]+tr[o<<1|1].dep[i];
	F(i,0,k-1)tr[o].dep[i]=tr[o<<1].cnt[i]+tr[o<<1|1].cnt[i];
}
int ask(int l,int r,int o,int a,int b,int c)
{
	if(a<=l && r<=b)return tr[o].cnt[c];
	int mid=l+r>>1;
	pushdown(o);
	if(b<=mid)return ask(l,mid,o<<1,a,b,c);
	if(a>mid) return ask(mid+1,r,o<<1|1,a,b,c);
	return ask(l,mid,o<<1,a,b,c)+ask(mid+1,r,o<<1|1,a,b,c);
}
struct oper
{
	int op,x,y;
}q[N];
int main()
{
	cin.tie(0)->sync_with_stdio(false);
	int testid;
	int n,m,nn=0;
	cin>>testid>>n>>m>>k;nn=n;
	F(i,1,n)cin>>fa[i],E[fa[i]].ep(i);
	F(i,1,m)
	{
		cin>>q[i].op>>q[i].x;
		if(q[i].op!=3)cin>>q[i].y;
		else fa[++n]=q[i].x;
	}
	dfs(1);
	F(i,1,nn)add(1,n,1,dfn[i],dep[i]);
	F(i,1,m)
	{
		int op=q[i].op,x=q[i].x,y=q[i].y;
		if(op==1)
		{
			cerr<<"modi"<<dfn[x]<<' '<<dfn[x]+sz[x]-1<<'\n';
			modify(1,n,1,dfn[x],dfn[x]+sz[x]-1,((y-dep[x])%k+k)%k);
		}
		if(op==2)
		{
			cerr<<"out"<<dfn[x]<<' '<<dfn[x]+sz[x]-1<<'\n';
			cout<<ask(1,n,1,dfn[x],dfn[x]+sz[x]-1,y%k)<<'\n';
		}
		if(op==3)
		{
			++nn;
			add(1,n,1,dfn[nn],dep[nn]);
		}
	}
	return 0;
}

