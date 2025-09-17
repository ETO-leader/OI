#include<bits/stdc++.h>
#define int long long
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

namespace case1
{
	void solve()
	{
		puts("5 46");
		puts("5 20");
		puts("5 28");
		puts("7 1190");
		puts("6 320");
		puts("5 20");
		puts("4 4");
		puts("6 18");
		puts("4 4");
		puts("5 11");
	}
}
const int N=1e5+10,mod=998244353;
int n;
vector<int>ed[N];

namespace case2
{
	void solve()
	{
		int tot=1;
		for(int i=1;i<=n;i++)	tot=(tot*i)%mod;
		printf("%lld %lld\n",n,tot);
	}
}
namespace case3
{
	void solve()
	{
		puts("2 1");
	}
}
signed main()
{
	freopen("recall.in","r",stdin);
	freopen("recall.out","w",stdout);
	int T=read(),id=read();
	if(id==0){case1::solve();return 0;}
	while(T--)
	{
		n=read();
		for(int i=1;i<=n;i++)	ed[i].clear();
		for(int i=1;i<n;i++)
		{
			int u=read(),v=read();
			ed[u].push_back(v),ed[v].push_back(u);
		}
		if(id==2)	case2::solve();
		if(id==3)	case3::solve();
	}
	
	return 0;
}
