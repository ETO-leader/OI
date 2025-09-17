#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define lll __int128
#define db double
#define ld long double
#define fi first
#define se second
#define endl '\n'
#define ainline inline __attribute__((always_inline))
#define inf 0x3f3f3f3f
#define ninf 0xcfcfcfcf
#define infll 0x3f3f3f3f3f3f3f3f
#define ninfll 0xcfcfcfcfcfcfcfcf
#define start_mtest\
	int tcnt;\
	cin>>tcnt;\
	for(int tcase=1;tcase<=tcnt;tcase++)[&]\
	{
#define end_mtest\
	}();
constexpr int N=200010;
string S,T;
int n,m;
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tcnt,tid;
	cin>>tcnt>>tid;
	for(int tcase=1;tcase<=tcnt;tcase++)[&]
	{
		cin>>S>>T;
		if(tid==6)return cout<<((T.size()-S.size())&1?"NO\n":"YES\n"),[]{}();
		S="@"+S+"@";T="@"+T+"@";
		n=S.size()-1;m=T.size()-1;
		int i,j;
		for(i=1,j=1;i<=n&&j<=m;)
		{
			while(i<n&&j<m&&S[i]==T[j]&&S[i]==S[i+1]&&T[j]==T[j+1])i+=2,j+=2;
			while(S[i]!=T[j])
			{
				if(j>=m||T[j]!=T[j+1])return cout<<"NO\n",[]{}();
				j+=2;
			}
			i++,j++;
		}
		if(i!=n+1||j!=m+1)cout<<"NO\n";
		else cout<<"YES\n";
	}();
	return 0;
}

