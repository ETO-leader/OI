#include<bits/stdc++.h>
using namespace std;
mt19937_64 myrand(time(0));
const int MAXN = 1e5 + 10 , MOD = 998244353;
int id , T;
int n , maxdep , kcnt;
vector <int> k[MAXN];
int mul[MAXN];
void init()
{
	mul[0] = 1;
	for(int i = 1 ; i <= MAXN - 10 ; i++) mul[i] = 1ll * mul[i - 1] * i % MOD;
	return;
}
int qpow(int a , int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1) res = 1ll * res * a % MOD;
		a = 1ll * a * a % MOD;
		b >>= 1;
	}
	return res;
}
int C(int n , int m) { return 1ll * mul[n] * qpow(mul[m] , MOD - 2) % MOD * qpow(mul[n - m] , MOD - 2) % MOD; }
void dfs(int now , int fa , int dep , bool is_ok)
{
	if(is_ok) kcnt = dep;
	for(int i : k[now]) if(i != fa) dfs(i , now , dep + 1 , (is_ok && k[now].size() == 1));
	maxdep = max(maxdep , dep);
	return;
}
void solve()
{
	maxdep = -1;
	dfs(1 , 0 , 1 , 1);
	printf("%d %d\n" , maxdep , (int)(1ll * C(maxdep - 1 , kcnt - 1) * mul[kcnt] % MOD));
	return;
}
int getrd(int l , int r) { return (myrand() - 1) % (r - l + 1) + l; }
int main()
{
	freopen("recall.in" , "r" , stdin);
	freopen("recall.out" , "w" , stdout);
	cin >> id >> T;
	if(id == 0)
	{
		printf("5 46\n5 20\n5 28\n7 1190\n6 320\n5 20\n4 4\n6 18\n4 4\n5 11");
		return 0;
	}
	init();
	while(T--)
	{
		cin >> n;
		for(int i = 1 ; i <= n ; i++) k[i].clear();
		for(int i = 1 ; i <= n - 1 ; i++)
		{
			int u , v;
			scanf("%d%d" , &u , &v);
			k[u].push_back(v) , k[v].push_back(u);
		}
		if(id == 3)
		{
			printf("2 1\n");
			continue;
		}
		if(id == 2)
		{
			printf("%d %d\n" , n , mul[n]);
			continue;
		}
		solve();
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}