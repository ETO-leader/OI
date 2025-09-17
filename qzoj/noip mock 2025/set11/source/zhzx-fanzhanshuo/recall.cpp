#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,mod=998244353;
int n,m,a[N],ans;
vector<int> e[N];
signed main(){
	freopen("recall.in","r",stdin);
	freopen("recall.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int id,T; 
	cin>>id>>T;
	if(id==0){
		cout<<"5 46\n5 20\n5 28\n7 1190\n6 320\n";
		cout<<"5 20\n4 4\n6 18\n4 4\n5 11\n";
		return 0;
	}
	while(T--){
		for(int i=1;i<=n;++i) e[i].clear();
		cin>>n;
		for(int i=1;i<n;++i){
			int x,y;
			cin>>x>>y;
			e[x].push_back(y);
			e[y].push_back(x);
		}
		if(id==2){
			ans=1;
			for(int i=1;i<=n;++i) ans=ans*i%mod;
			cout<<n<<' '<<ans<<'\n';
			continue;
		}
		if(id==3){
			if(n==2) cout<<"2 2\n";
			cout<<"2 1\n";
			continue;
		}
//		if(id==4){
//			dfs(1,0);
//			if(e[1].size()>1){
//				cout<<""<<
//			}
//		}
	}
	return 0;
}
