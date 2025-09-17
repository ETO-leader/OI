#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second
using namespace std;
int Time=clock();
bool mst;
const int N=20005;
struct node{
	int v,last;
};
node E[N];
int tp,n,m,K,head[N],p,color[N],lst;
void add(int a,int b){
	E[++p].v=b,E[p].last=head[a],head[a]=p;
}
void update(int a,int b){
	color[a]=b;
	for(int i=head[a];i>0;i=E[i].last)
		update(E[i].v,b+1>K?b+1-K:b+1);
}
int query(int a,int b){
	int ans=0;
	for(int i=head[a];i>0;i=E[i].last)
		ans+=query(E[i].v,b);
	if(color[a]==b)  ans++;
	return ans;
}
bool med;
int main(){
	freopen("grandiloquence.in","r",stdin);
	freopen("grandiloquence.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>tp>>n>>m>>K;
	for(int i=1;i<=n;i++){
		int t;
		cin>>t;
		if(t!=0)  add(t,i);
	}
	while(m--){
		int opt,u,c;
		cin>>opt>>u;
		if(opt!=3)  cin>>c;
		if(tp)  u^=lst,c^=lst;
		if(opt==1)  update(u,c);
		if(opt==2){
			lst=query(u,c);
			cout<<lst<<'\n';
		}
		if(opt==3)  add(u,++n);
	}
	// #ifndef ONLINE_JUDGE
	// cerr<<"Time:"<<fixed<<setprecision(5)<<1.0*(clock()-Time)/CLOCKS_PER_SEC<<"s"<<endl;
	// cerr<<"Memory:"<<fixed<<setprecision(5)<<1.0*(&med-&mst)/1024/1024<<"MB";
	// #endif
	return 0;
}