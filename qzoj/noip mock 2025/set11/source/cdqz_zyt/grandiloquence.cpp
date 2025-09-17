#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10;
int tp , lstans , nowcnt;
int n , m , k , fa[MAXN] , col[MAXN];
vector <int> a[MAXN];
void dfs1(int now , int fa , int dis , int dtval)
{
	col[now] = (dis + dtval - 1) % k + 1;
	for(int i : a[now]) if(i != fa) dfs1(i , now , dis + 1 , dtval);
	return;
}
void modify(int pos , int dtval)
{
	dfs1(pos , fa[pos] , 0 , dtval);
	return;
}
void dfs2(int now , int fa , int val)
{
	if(col[now] == val) nowcnt++;
	for(int i : a[now]) if(i != fa) dfs2(i , now , val);
	return;
}
int query(int pos , int val)
{
	nowcnt = 0;
	dfs2(pos , fa[pos] , val);
	printf("%d\n" , nowcnt);
	return nowcnt;
}
int main()
{
	freopen("grandiloquence.in" , "r" , stdin);
	freopen("grandiloquence.out" , "w" , stdout);
	cin >> tp;
	cin >> n >> m >> k;
	for(int i = 1 ; i <= n ; i++)
	{
		scanf("%d" , &fa[i]);
		a[fa[i]].push_back(i) , a[i].push_back(fa[i]);
	}
	while(m--)
	{
		int op;
		scanf("%d" , &op);
		if(op == 1)
		{
			int u , c;
			scanf("%d%d" , &u , &c);
			if(tp) u ^= lstans , c ^= lstans;
			modify(u , c);
		}
		if(op == 2)
		{
			int u , c;
			scanf("%d%d" , &u , &c);
			if(tp) u ^= lstans , c ^= lstans;
			lstans = query(u , c);
		}
		if(op == 3)
		{
			int u;
			scanf("%d" , &u);
			if(tp) u ^= lstans;
			n++;
			fa[n] = u;
			a[n].push_back(u) , a[u].push_back(n);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
/*
0
6 2 2
0 1 2 5 1 5
1 1 2
2 2 2
*/