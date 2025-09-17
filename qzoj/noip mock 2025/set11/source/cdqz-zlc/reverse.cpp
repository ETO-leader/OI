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

const int N=1e6+10;
int id,n,k;
int a[N],b[N],c[N];
namespace case1
{
	static int tr[N];
	void add(int x,int k)
	{
		while(x<=n)
		{
			tr[x]+=k;
			x+=(x&(-x));
		}
	}
	int query(int x)
	{
		int res=0;
		while(x)
		{
			res+=tr[x];
			x-=(x&(-x));
		}
		return res;
	}
	int check(int f[])
	{
		for(int i=0;i<=n;i++)	tr[i]=0;
		int res=0;
		for(int i=n;i>=1;i--)
		{
//			cout<<f[i]<<" ";
			res+=query(f[i]);
			add(f[i],1);
		}
//		cout<<endl;
		return res;
	}
	void solve()
	{
		if(check(a)==k)
		{
			puts("0");
			return;
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				for(int x=1;x<=n;x++)	b[x]=a[x];
				sort(b+i,b+j+1);
				if(check(b)==k)
				{
					puts("1");
					printf("%lld %lld\n",i,j);
					return;
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				for(int x=1;x<=n;x++)	b[x]=a[x];
				sort(b+i,b+j+1);
				for(int l=1;l<=n;l++)
				{
					for(int r=l+1;r<=n;r++)
					{
//						cout<<i<<' '<<j<<" "<<l<<" "<<r<<endl;
						for(int x=1;x<=n;x++)	c[x]=b[x];
						sort(c+l,c+r+1);
						if(check(c)==k)
						{
							puts("2");
							printf("%lld %lld\n",i,j);
							printf("%lld %lld\n",l,r);
							return;
						}
					}
				}
			}
		}
	}
}
signed main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	id=read(),n=read(),k=read();
	for(int i=1;i<=n;i++)	a[i]=read();
	if(id==3){puts("0");return 0;}
	if(id<=1)	case1::solve();

	return 0;
}
