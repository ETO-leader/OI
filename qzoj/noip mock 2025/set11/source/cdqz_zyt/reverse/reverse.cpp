#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 10;
int id , n;
long long k;
int a[MAXN] , cnt;
struct ANS
{
	int l;
	int r;
};
struct BIT
{
	int val[MAXN];
	void init()
	{
		memset(val , 0 , sizeof(val));
		return;
	}
	int lowbit(int x) { return x & (-x); } 
	void modify(int pos , int dtval)
	{
		int now = pos;
		while(now <= n)
		{
			val[now] += dtval;
			now += lowbit(now);
		}
		return;
	}
	int query(int pos)
	{
		int now = pos , res = 0;
		while(now)
		{
			res += val[now];
			now -= lowbit(now);
		}
		return res;
	}
};
BIT T;
ANS ans[MAXN];
long long getrev()
{
	T.init();
	long long res = 0;
	for(int i = 1 ; i <= n ; i++)
	{
		res += (i - 1) - T.query(a[i] - 1);
		T.modify(a[i] , 1);
	}
	return res;
}
int main()
{
	freopen("reverse.in" , "r" , stdin);
	freopen("reverse.out" , "w" , stdout);
	cin >> id >> n >> k;
	for(int i = 1 ; i <= n ; i++) scanf("%d" , &a[i]);
	k = getrev() - k;
	if(!k)
	{
		printf("0");
		return 0;
	}
	while(k)
	{
		int l = 1 , r = 0 , nowcnt = 0 , maxval = -1 , resl , resr;
		T.init();
		T.modify(a[++r] , 1);
		while(l <= r)
		{
			if(nowcnt <= k && r + 1 <= n)
			{
				r++;
				nowcnt += (r - l) - T.query(a[r] - 1);
				T.modify(a[r] , 1);
			}
			else if(l <= n)
			{
				nowcnt -= T.query(a[l] - 1);
				T.modify(a[l] , -1);
				l++;
			}
			if(nowcnt <= k && nowcnt > maxval)
			{
				maxval = nowcnt;
				resl = l , resr = r;
			}
		}
		ans[++cnt] = {resl , resr};
		sort(a + resl , a + resr + 1);
		k -= maxval;
	}
	printf("%d\n" , cnt);
	for(int i = 1 ; i <= cnt ; i++) printf("%d %d\n" , ans[i].l , ans[i].r);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
/*
0 5 3
2 3 5 4 1
*/