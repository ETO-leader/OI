#include<bits/stdc++.h>
using namespace std;
const int maxn=40005;
int read(){
	char ch=getchar();int ret=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+(ch&15),ch=getchar();
	return ret*f;
}
int subid,n,m,k,fa[maxn],lastans,lstans,col[maxn],head[maxn],tot;
struct edge{int u,v;int nxt;}e[maxn];
void add_edge(int x,int y){e[++tot]=(edge){x,y,head[x]};head[x]=tot;}
void dfscol(int x,int co){col[x]=co;for(int j=head[x];j;j=e[j].nxt){if(e[j].v==fa[x])continue;dfscol(e[j].v,co%k+1);}}
int querycol(int x,int co){int ret=0;if(col[x]==co)ret++;for(int j=head[x];j;j=e[j].nxt){if(e[j].v==fa[x])continue;ret+=querycol(e[j].v,co);}return ret;}
signed main(){
    freopen("grandiloquence.in","r",stdin);
    freopen("grandiloquence.out","w",stdout);
    subid=read();n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++)fa[i]=read(),add_edge(i,fa[i]),add_edge(fa[i],i);
    while(m--){
        int flg=read();
        if(flg==1){int x=read(),c=read();if(subid%2==0)x=x^lstans,c=c^lstans;dfscol(x,c);
        }else if(flg==2){int x=read(),c=read();if(subid%2==0)x=x^lstans,c=c^lstans;printf("%d\n",querycol(x,c));
        }else{int x=read();if(subid%2==0)x=x^lstans;n++;fa[n]=x;add_edge(n,x);add_edge(x,n);}
    }
    return 0;
}
