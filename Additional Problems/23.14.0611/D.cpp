#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e4+7;
struct edge{int v;bool del;};
vector<vector<edge>> G;
auto bfs(int u){
	const int n=G.size()-1;
	VI D(n+1,_inf),vis(n+1),fx(n+1);
	queue<int> q;q.push(u);D[u]=0;
	while(!q.empty()){
		int f=q.front();q.pop();
		vis[f]=true;
		for(auto&[v,del]:G[f]){
			if((!del)&&(!vis[v])){
				D[v]=D[f]+1;q.push(v);
				vis[v]=true;fx[v]=f;
			}
		}
	}
	return make_pair(D,fx);
}
struct edge_t{int u,v,iu;};
auto fndrd(int frm,VI&fx){
	int u=G.size()-1;
	set<pair<int,int>> vis;
	while(u!=frm){
		vis.insert({u,fx[u]});
		vis.insert({fx[u],u});
		//cout<<u<<' ';
		u=fx[u];
	}
	//cout<<u<<'\n';
	return vis;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
	G.resize(n+1);vector<edge_t> E(m);
	for(auto&[u,v,iu]:E){
		cin>>u>>v;iu=G[u].size();
		G[u].push_back({v,false});
	}
	auto [D,fx]=bfs(1);
	if(D[n]>=_inf){
		cir(i,0,m) cout<<"-1\n";
		exit(0);
	}
	//cir(i,1,n+1) cout<<D[i]<<' ';
	//cout<<'\n';
	//cout<<n<<":"<<D[n]<<'\n'<<'\n';
	auto inr=fndrd(1,fx);
	for(auto&[u,v,iu]:E){
		if(inr.count({u,v})){
			G[u][iu].del=true;
			cout<<[&](){
				int w=bfs(1).first[n];
				return w>=_inf?-1:w;
			}()<<'\n';
			G[u][iu].del=false;
		}else{
			cout<<(D[n]>=_inf?-1:D[n])<<'\n';
		}
	}
	return 0;
}
