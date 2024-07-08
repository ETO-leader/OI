#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
vector<int> D,D1,C;
int dfs1(int u,int f=0){
	int& d=D[u],&d1=D1[u];d=d1=0;
	for(int&i:G[u]){
		if(i==f) continue;
		int di=dfs1(i,u)+1;
		if (di>d) d1=d,d=di,C[u]=i;
		else if(di>d1) d1=di;
	}
	return d;
}
void dfs2(int u,int f=0){
	for(int&i:G[u]){
		if(i==f) continue;
		int&d=D[i],&d1=D1[i],&c=C[i];
		if(C[u]==i){
			if(d<D1[u]+1) d1=d,d=D1[u]+1,c=u;
			else d1=max(d1,D1[u]+1);
		}else{
			d1=d,d=D[u]+1,c=u;
		}
		dfs2(i,u);
	}
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n;cin>>n;G.resize(n+1);D.resize(n+1);
	D1.resize(n+1);C.resize(n+1);
	cir(i,0,n-1){
		int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
	}
	dfs1(1);dfs2(1);
	cir(i,1,n+1) cout<<D[i]<<' ';
    cout<<'\n';
	return 0;
}
