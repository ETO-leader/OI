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
constexpr int N=1e5+9;
namespace bit
{
	int n,tr[N];
	void add(int x,int k)
	{
		for(int i=x;i<=n;i+=i&-i)tr[i]+=k;
	}
	int ask(int x)
	{
		int ans=0;
		for(int i=x;i;i-=i&-i)ans+=tr[i];
		return ans;
	}
}
ll pre[N],suf[N];
int a[N];
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
constexpr int B=330;
struct node
{
	int l,r,w,id;
	bool operator<(const node&A)const
	{
		if(l/B!=A.l/B)return l<A.l;
		if((l/B)&1)return r>A.r;
		return r<A.r;
	}
}q[N<<2];
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	cin.tie(0)->sync_with_stdio(false);
	int id,n;ll k;
	cin>>id>>n>>k;
	bit::n=n;
	F(i,1,n)cin>>a[i];
	vector<pii> out;
	while(1)
	{
		ll sum=0;
		memset(bit::tr,0,sizeof bit::tr);
		F(i,1,n)
		{
			sum+=i-1-bit::ask(a[i]);
			bit::add(a[i],1);
		}
		ll sk=sum-k;
		if(sk==0)break;
		memset(bit::tr,0,sizeof bit::tr);
		sum=0;
		int l=1;
		pii ss=mp(-1,-1);ll tt=0;
		F(i,1,n)
		{
			sum+=i-l-bit::ask(a[i]);
			bit::add(a[i],1);
			while(sum>sk)
			{
				bit::add(a[l],-1);
				sum-=bit::ask(a[l]);
				l++;
			}
			if(sum>=tt)
			{
				ss=mp(l,i);
				tt=sum;
			}
		}
		out.ep(ss);
		sort(a+ss.x,a+ss.y+1);
	}
	cout<<out.size()<<'\n';
	for(auto u:out)cout<<u.x<<' '<<u.y<<'\n';
	return 0;
}

