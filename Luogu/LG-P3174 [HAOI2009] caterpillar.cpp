#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
vector<int> D;
void dfs(int u,int f=0){
    cout<<u<<' '<<D[u]<<endl;
	int mx=0;
	for(auto&i:G[u]){
		if(i==f) continue;
		dfs(i,u);mx=max(mx,D[i]);
	}
	(D[u]=max(D[u],mx+1+(int)(G[u].size()>2?G[u].size()-2:0)));
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n,m;cin>>n>>m;G.resize(n+1);D.resize(n+1);
	if(n==1){cout<<1<<endl;exit(0);}
	cir(i,0,n-1){
		int u,v;cin>>u>>v;
		G[u].push_back(v);G[v].push_back(u);
	}
    int st=0,stx=1;
    cir(i,1,n+1) if(st<G[i].size()) st=G[i].size(),stx=i;
	dfs(stx);priority_queue<int> pq;
	for(auto&i:G[stx]){
		pq.push(D[i]);
	}
	int x=pq.top();pq.pop();if(!pq.empty()) x+=pq.top();
	cout<<max(x+1+(int)(G[stx].size()>2?G[stx].size()-2:0),D[stx])<<endl;
	return 0;
}