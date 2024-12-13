#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<set>
using namespace std;
#define R register int
#define I inline void
const int N=100009,M=N<<1;
#define lc c[x][0]
#define rc c[x][1]
#define C lct[col[x]]
#define G ch=getchar()
template<typename T>
I gi(register T&z){
	register char G;register bool fl=0;
	while(ch<'-')G;
	if(ch=='-')fl=1,G;
	z=ch&15;G;
	while(ch>'-')z*=10,z+=ch&15,G;
	if(fl)z=-z;
}
int fa[N],v[N],he[N],ne[M],to[M];
bool col[N];
struct LCT{
	int f[N],c[N][2],mx[N];
	bool r[N];
	multiset<int>s[N];
	LCT(){mx[0]=-2147483647;}//因为点权可能为负，所以空节点要设成-inf
	inline bool nroot(R x){return c[f[x]][0]==x||c[f[x]][1]==x;}
	I pushup(R x){
		mx[x]=max(v[x],max(mx[lc],mx[rc]));
		if(!s[x].empty())mx[x]=max(mx[x],*s[x].rbegin());
	}
	I rotate(R x){
		R y=f[x],z=f[y],k=c[y][1]==x,w=c[x][!k];
		if(nroot(y))c[z][c[z][1]==y]=x;c[x][!k]=y;c[y][k]=w;
		f[w]=y;f[y]=x;f[x]=z;
		pushup(y);
	}
	I splay(R x){
		R y;
		while(nroot(x)){
			if(nroot(y=f[x]))rotate((c[f[y]][0]==y)^(c[y][0]==x)?x:y);
			rotate(x);
		}
		pushup(x);
	}
	I access(R x){
		for(R y=0;x;x=f[y=x]){
			splay(x);
			if(rc)s[x].insert(mx[rc]);
			if((rc=y))s[x].erase(s[x].find(mx[y]));
			pushup(x);
		}//跟维护信息和有点像，也是加一个减一个
	}
	inline int findroot(R x){
		access(x);splay(x);
		while(lc)x=lc;
		splay(x);
		return x;
	}
	I link(R x){
		splay(x);
		R y=f[x]=fa[x];
		access(y);splay(y);
		c[y][1]=x;pushup(y);
	}//另一种link写法，也是看Kelin巨佬代码学的
//这里连的是实边，因为连虚边更新信息还有点麻烦
	I cut(R x){
		access(x);splay(x);
		lc=f[lc]=0;
		pushup(x);
	}
	I update(R x){
		access(x);splay(x);
		gi(v[x]);pushup(x);
	}
}lct[2];
void dfs(R x,R y){
	fa[x]=y;
	for(R i=he[x];i;i=ne[i])
		if(to[i]!=y)dfs(to[i],x);
	C.link(x);
}
int main(){
	R p=1,n,m,i,x,y,op;
	gi(n);
	for(i=1;i<n;++i){
		gi(x);gi(y);
		to[++p]=y;ne[p]=he[x];he[x]=p;
		to[++p]=x;ne[p]=he[y];he[y]=p;
	}
	for(i=1;i<=n;++i)gi(col[i]);
	for(i=1;i<=n;++i)gi(v[i]);
	dfs(1,fa[1]=n+1);
	gi(m);
	while(m--){
		gi(op);gi(x);
		switch(op){
		case 0:printf("%d\n",C.mx[C.c[C.findroot(x)][1]]);break;
		case 1:C.cut(x);col[x]^=1;C.link(x);break;
		case 2:C.update(x);
//AC后和Kelin巨佬的代码对比，发现我只更新了一个LCT中的，居然对了？！
//跟我的写法有关吧。。。。。。因为每次findroot我都splay到了根，直接改是对的吧
		}
	}
    return 0;
}