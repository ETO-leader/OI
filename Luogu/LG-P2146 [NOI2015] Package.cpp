#include<bits/stdc++.h>
using namespace std;
template<typename T>
struct odt{
	struct Node{
		int l,r;mutable T v;
		bool operator<(const Node&n) const{
			return l<n.l;
		}
	};
	set<Node> Sn;int n;
	odt(int _n=0):n(_n){
		Sn.insert({0,n,0});
	}
	void resize(int n){(*this)=odt(n);}
	auto split(int k){
		if(k>n) return Sn.end();
		auto it=--Sn.upper_bound(k);
		if(it->l==k) return it;
		auto l=it->l,r=it->r,v=it->v;
		Sn.erase(it);Sn.insert({l,k,v});
		return Sn.insert({k+1,r,v}).first;
	}
	void assign(int l,int r,int v){
		auto il=split(l),ir=split(r);
		Sn.erase(il,ir);Sn.insert({l,r,v});
	}
	int count(int l,int r){
		auto il=split(l),ir=split(r);int ret=0;
		for(il;il!=ir;++il) ret+=(il->v)*(il->r-il->l+1);
		return ret;
	}
};
//Chtholly Tree
odt<bool> cht;
struct edge{int v;bool isheavy;};
vector<vector<edge>> G;
vector<int> Fa,Ht,Hvs;
int dfs(int u){
	if(G[u].empty()) return 1;
	int mx=0,k=0,cnt=0,cx=1;
	for(auto&i:G[u]){
		int d=dfs(i.v);
		if(d>mx) mx=d,k=cnt;
		++cnt,cx+=d;
	}
	Hvs[u]=k;
	return cx;
}
vector<int> id,Rt;
int IdCnt=0;
void Split(int u,int rt){
	if(G[u].empty()) return; // Leaf Node
	int cnt=0;//Edge id
	id[u]=++IdCnt;Rt[u]=rt;
	G[u][Hvs[u]].isheavy=true;
	Split(G[u][Hvs[u]].v,rt);
	//Heavy Edge first Go
	for(auto&i:G[u]){
		if(cnt!=Hvs[u]) Split(i.v,i.v);
	}
}
void Jump(int k,int v){
	while((k!=1)&&(Rt[k]!=v)){
		
	}
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);

	return 0;
}