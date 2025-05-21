#include <bits/stdc++.h>
#include "b.h"
const int N = 1e5 + 5,Lg = 18;

namespace {
	int n,SubId;
	std::vector<int> G[N];
	std::set<std::pair<int,int> > ES;
	int ST[Lg][N],dfn[N],dep[N];
	inline int Min(int x,int y) { return dfn[x] < dfn[y] ? x : y;}
	inline void dfs0(int x,int fa) {
		ST[0][dfn[x] = ++dfn[0]] = fa;
		dep[x] = dep[fa] + 1;
		for(auto y : G[x])
			if(y != fa) dfs0(y,x);
	}
	inline void quitWA(int id) {
		printf("WrongAnswer[%d]\n",id);
		exit(0);
	}
	inline int lca(int x,int y) {
		if(x == y) return x;
		x = dfn[x];y = dfn[y];
		if(x > y) std::swap(x,y);
		int k = std::__lg(y - (x++));
		return Min(ST[k][x],ST[k][y-(1<<k)+1]);
	}
	inline int dis(int x,int y) { return dep[x] + dep[y] - 2 * dep[lca(x,y)];}
	int sumA,sumB;
	int ufs[N];
	int getfa(int x) { return ufs[x] == x ? x : ufs[x] = getfa(ufs[x]);}
}	
bool Ask(int x,std::vector<int> S) {
	if(x < 1 || x > n) quitWA(1);
	for(auto i : S) if(i < 1 || i > n) quitWA(1);
	if(S.empty()) quitWA(2);
	++sumA;sumB += S.size();
	int mi = S[0],mx = S[0];
	for(auto i : S) {
		if(dfn[i] < dfn[mi]) mi = i;
		if(dfn[i] > dfn[mx]) mx = i;
	}
	int p = lca(mi,mx);
	for(auto i : S)
		if(dis(p,x) + dis(x,i) == dis(p,i)) return true;
	return false;
}
int main() {
	std::cin >> n >> SubId;
	for(int i = 1,u,v;i < n;i++) {
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
		ES.emplace(std::min(u,v),std::max(u,v));
	}
	dfs0(1,0);
	for(int j = 1;j < Lg;j++)
		for(int i = 1;i + (1 << j) - 1 <= n;i++)
			ST[j][i] = Min(ST[j - 1][i],ST[j - 1][i + (1 << j - 1)]);
	std::vector<std::pair<int,int> > PS = Solve(n,SubId);
	if(PS.size() != n - 1) quitWA(3);
	for(int i = 1;i <= n;i++) ufs[i] = i;
	for(auto it : PS) {
		if(getfa(it.first) == getfa(it.second)) quitWA(3);
		ufs[getfa(it.first)] = getfa(it.second);
	}
	std::set<std::pair<int,int> > S2;
	for(auto it : PS) {
		int u = it.first,v = it.second;
		S2.emplace(std::min(u,v),std::max(u,v));
	}
	if(ES != S2) quitWA(4);
	std::printf("Correct! %d %d\n",sumA,sumB);
	return 0;
}
