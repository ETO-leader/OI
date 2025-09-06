#include<bits/stdc++.h>
#define MAXN 505
#define reg register
#define inl inline
using namespace std;
int A,n,Mod,a[MAXN],lim,f[MAXN][MAXN<<1],y[MAXN];
inl int Add(reg int x,reg int y)
{
	return x+y>Mod?x+y-Mod:x+y;
}
inl int Del(reg int x,reg int y)
{
	return x-y<0?x-y+Mod:x-y;
}
inl int Mul(reg int x,reg int y)
{
	return 1ll*x*y-1ll*x*y/Mod*Mod;
}
inl int Pow(reg int x,reg int y)
{
	reg int res=1;
	for(;y;y>>=1,x=Mul(x,x)) if(y&1) res=Mul(res,x);
	return res;
}
inl int Lagrange(reg int x)
{
	if(1<=x && x<=lim) return y[x];
	reg int res=0;
	for(reg int i=1;i<=lim;i++)
	{
		reg int Up=1,Dn=1;
		for(reg int j=1;j<=lim;j++)
		{
			if(i==j) continue;
			Up=Mul(Up,Del(x,j));
			Dn=Mul(Dn,Del(i,j));
		}
		res=Add(res,Mul(y[i],Mul(Up,Pow(Dn,Mod-2))));
	}
	return res;
}
int main()
{
	scanf("%d %d %d",&A,&n,&Mod);
	lim=(n<<1)+1;
	for(reg int i=0;i<=lim;i++) f[0][i]=1;
	for(reg int i=1;i<=n;i++)
	{
		for(reg int j=1;j<=lim;j++) f[i][j]=Add(f[i][j-1],Mul(f[i-1][j-1],j));
	}
	for(reg int i=1;i<=lim;i++) y[i]=f[n][i];
	reg int ans=Lagrange(A);
	for(reg int i=1;i<=n;i++) ans=Mul(ans,i);
	printf("%d\n",ans);
	return 0;
}
