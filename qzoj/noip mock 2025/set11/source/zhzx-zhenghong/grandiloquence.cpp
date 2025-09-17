#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
void write(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
int subid;
int n,m,k;
int fa[N];
struct edge{
	int u,v;
	int nxt;
}e[N];
int head[N],tot;
void add_edge(int x,int y){
	e[++tot]=(edge){x,y,head[x]};head[x]=tot;
}
int col[N];
void dfscol(int x,int co){
	col[x]=co;
	for(int j=head[x];j;j=e[j].nxt){
		if(e[j].v==fa[x])continue;
		dfscol(e[j].v,co%k+1);
	}
}
int lstans;
int querycol(int x,int co){
	int ret=0;if(col[x]==co)ret++;
	for(int j=head[x];j;j=e[j].nxt){
		if(e[j].v==fa[x])continue;
		ret+=querycol(e[j].v,co);
	}
	return ret;
}
//int a[N],b[N];
//void dfs_sq(int x,int tp){
//	a[tp]=x;b[x]=tp;
//	for(int j=head[x];j;j=e[j].nxt){
//		if(e[j].v==fa[x])continue;
//		dfs_sq(e[j].v,tp+1);
//	}
//}
//int tree[10][N<<2];
//int tag[10][N<<2];
//int ls[N<<2],rs[N<<2];
//int ver[N],dcnt;
//void build(int &x,int l,int r){
//	if(x==0)x=++dcnt;if(l==r)return;
//	int mid=(l+r)/2;
//	build(ls[x],l,mid);
//	build(rs[x],mid+1,r);
//}
signed main(){
	freopen("grandiloquence.in","r",stdin);
	freopen("grandiloquence.out","w",stdout);
	subid=read();n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)fa[i]=read(),add_edge(i,fa[i]),add_edge(fa[i],i);
//	if(subid==9 || subid==10){
//		dfs_sq(1,1);
//		while(m--){
//			int flg=read();
//			if(flg==1){
//				int x=read(),c=read();
//				if(subid%2==0)x=x^lstans,c=c^lstans;
//			}else if(flg==2){
//				int x=read(),c=read();
//				if(subid%2==0)x=x^lstans,c=c^lstans;
//			}
//		}
//		return 0;
//	}
//	if(subid==0 || subid==1 || subid==2){
		while(m--){
			int flg=read();
			if(flg==1){
				int x=read(),c=read();
				if(subid%2==0)x=x^lstans,c=c^lstans;
				dfscol(x,c);
			}else if(flg==2){
				int x=read(),c=read();
				if(subid%2==0)x=x^lstans,c=c^lstans;
				write(lstans=querycol(x,c));putchar('\n');
			}else{
				int x=read();
				if(subid%2==0)x=x^lstans;
				n++;fa[n]=x;add_edge(n,x);add_edge(x,n);
			}
		}
		return 0;
//	}
	return 0;
}
