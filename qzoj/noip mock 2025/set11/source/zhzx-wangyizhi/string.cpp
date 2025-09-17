#include<bits/stdc++.h>
//#include<bits/extc++.h>
//bool Mst;
using namespace std;
using ll=long long;
using ld=long double;
//#define int ll
using pii=pair<int,int>;
const int N=1e5+1;
//bool Med;
signed main()
{
//	cerr<<"Memory Size: "<<abs((&Med)-(&Mst))/1024.0/1024<<" MB\n";
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int t,id;
	cin>>t>>id;
	if(id==6) // aaaaaaaa
	{
		while(t--) [&]()->void
		{
			string s,t;
			cin>>s>>t;
			int n=s.length(),m=t.length(),ca=0,cc=0,ta=0;
			s=" "+s,t=" "+t;
			for(int i=1;i<=m;i++) ta+=t[i]=='a';
			for(int i=1;i<=m;)
			{
				if(i<m&&t[i]==t[i+1]) i+=2;
				else
				{
					if(t[i]=='a') ca++;
					else cc++;
					i++;
				}
			}
			if(!cc&&ta>=n&&ca<=n&&(ca-n)%2==0) cout<<"YES\n";
			else cout<<"NO\n";
		}();
		return 0;
	}
	while(t--)
	{
		string s,t;
		cin>>s>>t;
		int n=s.length(),m=t.length();
		s=" "+s,t=" "+t;
		vector<bitset<N>> dp(n+1);
		for(int i=0;i<=n;i++) dp[i].reset();
		dp[0][0]=1;
		for(int i=0;i<=n;i++)
		{
			for(int j=0;j<=m;j++) if(dp[i][j])
			{
				if(j<=m-2&&t[j+1]==t[j+2]) dp[i][j+2]=1;
				if(i<=n-1&&j<=m-1&&s[i+1]==t[j+1]) dp[i+1][j+1]=1;
			}
		}
		if(dp[n][m]) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
