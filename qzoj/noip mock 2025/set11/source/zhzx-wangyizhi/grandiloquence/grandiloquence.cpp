#include<bits/stdc++.h>
//#include<bits/extc++.h>
//bool Mst;
using namespace std;
using ll=long long;
using ld=long double;
//#define int ll
using pii=pair<int,int>;
const int N=2e5+5;
vector<int> g[N];
int k,a[N];
void dfs(int u,int c)
{
	a[u]=c;
	for(int v:g[u]) dfs(v,c%k+1);
}
int query(int u,int c)
{
	int ans=(a[u]==c);
	for(int v:g[u]) ans+=query(v,c);
	return ans;
}
//bool Med;
signed main()
{
//	cerr<<"Memory Size: "<<abs((&Med)-(&Mst))/1024.0/1024<<" MB\n";
//	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	freopen("grandiloquence.in","r",stdin);
	freopen("grandiloquence.out","w",stdout);
	int id;
	cin>>id;
	int n,m,lstans=0;
	cin>>n>>m>>k;
	for(int i=1,x;i<=n;i++) cin>>x,g[x].push_back(i);
	while(m--)
	{
		int op,u,c;
		cin>>op>>u;u^=lstans;
		if(!(id%2)&&(op==1||op==2)) cin>>c,c^=lstans;
		if(op==1) dfs(u,c);
		else if(op==2) cout<<(lstans=query(u,c))<<"\n";
		else if(op==3) g[u].push_back(++n);
	}
	return 0;
}
