#include<bits/stdc++.h> 
using namespace std;
const int N=2e5+50;
struct node{
	int nxt,to; 
}r[N];int head[N],tot;
void add(int u,int v){
	r[++tot]={head[u],v};
	head[u]=tot;
}
int k,t[N];
void dfs(int x,int c){
	t[x]=c;
	c++;if(c>k) c=1;
	for(int i=head[x];i;i=r[i].nxt){
		int v=r[i].to;
		dfs(v,c);
	}
}
int get(int x,int c){
	int ret=0;
	if(t[x]==c) ret++;
	for(int i=head[x];i;i=r[i].nxt){
		int v=r[i].to;
		ret+=get(v,c);
	}
	return ret;
}
int main(){
	freopen("grandiloquence.in","r",stdin);
	freopen("grandiloquence.out","w",stdout);
	int tp,n,m;
	scanf("%d %d %d %d",&tp,&n,&m,&k);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		if(i!=1)add(x,i);
	}
	int las=0;
	while(m--){
		int ki,u;scanf("%d %d",&ki,&u);
		if(tp)u^=las;
		if(ki==1){
			int c;scanf("%d",&c);
			if(tp)c^=las;
			dfs(u,c);
		}
		if(ki==2){
			int c;scanf("%d",&c);
			if(tp)c^=las;
			las=get(u,c);
			printf("%d\n",las);
		}
		if(ki==3){
			add(u,++n);
		}
	}
}
/*
0 10 8 3
0 1 2 3 4 5 6 7 8 9
1 2 3
1 5 2
2 3 1
2 1 2
3 4
3 7
1 2 1
2 1 3
*/
