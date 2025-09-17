#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
//#define int long long
void init();void Solve();
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	freopen("grandiloquence.in","r",stdin);
	freopen("grandiloquence.out","w",stdout);
	int T=1;init();
//	cin>>T;
	while(T--) Solve();
	return 0;
}
void init(){
}
int id,n,m,k,col[400005],lst;
vector<int>q[400005];
void dfs1(int u,int dep,int co){
	col[u]=(dep+co-1)%k+1;
	for(int v:q[u]) dfs1(v,dep+1,co);
}
int dfs2(int u,int co){
	int res=0;
	if(col[u]==co) res=1;
	for(int v:q[u]) res+=dfs2(v,co);
	return res;
}
void Solve(){
	cin>>id>>n>>m>>k;
	for(int i=1,u;i<=n;i++){
		cin>>u;
		q[u].push_back(i);
	}
	for(int i=1,lop,u,c;i<=m;i++){
		cin>>op;
		if(op==1){
			cin>>u>>c;
			if(id%2==0) u^=lst,c^=lst;
			dfs1(u,0,c);
		}
		else if(op==2){
			cin>>u>>c;
			if(id%2==0) u^=lst,c^=lst;
			cout<<(lst=dfs2(u,c))<<endl;
		}
		else{
			cin>>u;
			if(id%2==0) u^=lst;
			q[u].push_back(++n);
		}
	}
}

