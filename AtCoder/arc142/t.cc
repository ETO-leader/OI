#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int mod=1e9+7;
#define inf 1e9
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=8005;
int n,m,tp[N],Ans,Sum,X,Y,cnt,f[N],g[N];
int main(){
	n=read();
	for(int i=1,a,b,c,d;i<=n;i++){
		a=read(),b=read(),c=read(),d=read();
		if(a==c&&b==d){
			if(a==2)Sum+=i,++X;
			if(b==2)Sum+=i,++Y;
		}else if(a==c){
			if(a==2)Sum+=i,++X;
			tp[i]=2;
		}else if(b==d){
			if(b==2)Sum+=i,++Y;
			tp[i]=1;
		}else if(a==b)tp[i]=3;
		else ++cnt,Sum+=i;
	}
	for(int i=0;i<=n;i++){
		f[i]=g[i]=-i*(i+1)/2;
		for(int j=n,a=i,b=f[i];j;--j)
			if(tp[j]==1) clog<<"??!! "<<i<<' '<<j<<' '<<a<<' '<<b<<' '<<b+j-a-1<<'\n',++a,b+=j-a,f[i]=max(f[i],b);
		for(int j=n,a=i,b=g[i];j;--j)
			if(tp[j]==2)++a,b+=j-a,g[i]=max(g[i],b);
	}Ans=-inf;
	for(auto i=0;i<n+1;++i) clog<<f[i]<<' ';
	clog<<'\n';
	for(auto i=0;i<n+1;++i) clog<<g[i]<<' ';
	clog<<'\n';
	for(int i=0;i<=cnt;i++){
		Ans=max(Ans,f[X+i]+g[Y+cnt-i]);
		for(int j=n,a=0,b=0;j;--j)if(tp[j]==3)
			++a,b+=j+j,Ans=max(Ans,f[X+i+a]+g[Y+cnt-i+a]+b),clog<<X<<' '<<Y<<' '<<i<<' '<<j<<' '<<a<<' '<<b<<' '<<f[X+i+a]<<' '<<g[Y+cnt-i+a]<<' '<<b<<'\n';
	}printf("%d\n",Ans+Sum);
	return 0;
}

