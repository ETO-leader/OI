#include<bits/stdc++.h>
#define F(i,l,r) for(int i=(l),i##end=(r);i<=i##end;++i)
#define G(i,l,r) for(int i=(l),i##end=(r);i>=i##end;--i)
#define pii pair<int,int>
#define x first
#define y second
#define mp(x,y) make_pair(x,y)
#define ep emplace_back
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N=1e5+9;
constexpr int V=1e5;
/*
struct bitset
{
	ull a[(N>>6)+9];
	void init()
	{
		memset(a,0,sizeof a);
	}
	inline void flip(int x)
	{
		a[x>>6]^=1ull<<(x&63);
	}
}
*/
bitset<N> ch[26],dp[3];
void solve()
{
	string s,t;
	cin>>s>>t;
	F(i,0,25)ch[i].reset();
	F(i,0,(int)s.size()-1)ch[s[i]-'a'][i+1]=1;
	dp[0].reset();
	dp[1].reset();
	dp[1][0]=1;
	F(i,0,t.size()-1)
	{
		dp[2].reset();
		if(i>=1&&t[i]==t[i-1])dp[2]=dp[0];
		dp[2]|=(dp[1]<<1)&(ch[t[i]-'a']);
		dp[0]=dp[1];
		dp[1]=dp[2];
	}
	if(dp[2][s.size()])cout<<"YES\n";
	else cout<<"NO\n";
}
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	cin.tie(0)->sync_with_stdio(false);
	int T,id;
	cin>>T>>id;
	while(T--)solve();
	return 0;
}
