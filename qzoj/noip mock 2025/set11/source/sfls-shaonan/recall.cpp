#include<iostream>
#include<fstream>
#include<vector>
std::ifstream fin("recall.in");
std::ofstream fout("recall.out");
#define int long long 

const int mod = 998244353;
std::vector<int> e[100005];
std::vector<int> son[100005];
int dep[100005], f[100005], maxdep[100005];
int ok[100005][105], who[100005][105], pre[150][150], sum[150];

void build(int x, int ff) {
	f[x] = ff; 
	dep[x] = dep[ff]+1; maxdep[x] = dep[x];
	for (auto v : e[x]) {
		if (v != ff) {
			son[x].push_back(v);
			build(v,x);
			maxdep[x] = std::max(maxdep[x], maxdep[v]);
		}
	}
}

int dp(int x, int much) {
	if ((maxdep[x] - dep[x]) <= much) return 1;
	int ret = 0;
	ret += dp(x,much+1);
	for (int i = 1; i <= maxdep[x] - dep[x]; ++i) {
		if (much >= ok[x][i]) {
			if (maxdep[who[x][i]] - dep[who[x][i]] + 1 <= much) break;
			ret += dp(who[x][i], much+1) * pre[maxdep[x]-dep[x]+1-much-i-1][i] % mod * sum[i] % mod; ret %= mod;
			//std::cout << ret <<"\n";
		}
		else break;
	} 
	//std::cout << x <<" "<<much <<" "<<ret <<"\n";
	return ret;
}

void solve() {
	int n;fin >> n;
	for (int i = 1; i< n; ++i) {
		int u, v;
		fin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	build(1, 0);
	for (int i = 1; i <= n; ++i) {
		ok[i][0] = 0; who[i][0] = i; int now = i;
		for (int j = 1; j <= maxdep[i]-dep[i]; ++j) {
			int maxi = dep[now], whom, secmax = dep[now];
			for (auto v : son[now]) {
				if (maxdep[v] > maxi) {
					secmax = maxi, maxi = maxdep[v], whom = v;
				}
				else if (maxdep[v] > secmax) {
					secmax = maxdep[v];
				}
			}
			ok[i][j] = secmax - dep[now]; who[i][j] = whom; now = whom;
			//if (n == 10) std::cout << ok[i][j] <<" "<<who[i][j] <<" "<<i <<" "<<j <<"\n";
		}
	}
	fout << maxdep[1] <<" ";
	fout << dp(1,0) <<"\n";
	for (int i =1 ; i<= n; ++i) {
		e[i].clear(), son[i].clear();
	}
}

signed main() {
	sum[0] = 1;
	for (int i = 1; i <= 110; ++i) {
		sum[i] = sum[i-1] * i % mod; 
	}
	for (int i = 0; i <= 110; ++i) {
		for (int j = 0; j <= 110; ++j) {
			if (i == 0 || j == 0) pre[i][j] = 1;
			else pre[i][j] = pre[i-1][j] + pre[i][j-1];
			pre[i][j] %= mod;
		}
	}
	int id, t; fin >> id >> t;
	while (t --> 0) {
		solve();
	}
}
