#include<bits/stdc++.h>
#define maxn 1050005
#define fi first
#define se second
#define pii pair<int,int>
#define lowbit(x) ((x)&-(x))
#define conc(x,y,w) son[x][w]=y,fa[y]=x
#define int long long
typedef long long ll;
//inline ll sqr(ll x){return x*x;}
inline ll min(ll x,ll y){return x+=(y<x)*(y-x);}
inline ll max(ll x,ll y){return x+=(x<y)*(y-x);}
inline ll min(ll x,ll y,ll z){return min(min(x,y),z);}
inline ll max(ll x,ll y,ll z){return max(max(x,y),z);}
using namespace std;
mt19937_64 yrand((std::chrono::high_resolution_clock::now()).time_since_epoch().count());
const int Mod=998244353,L=2e6+10,inf=(int)1e9+7,Inv=(Mod+1)/2,FM=402653184,Blen=450,G=3,iG=(Mod+1)/G,V=1e9;
inline int reduce(int x){return x-(x>=Mod)*Mod;}
inline int reduce(int x,int Mod){return x-(x>=Mod)*Mod;}

int C,n,k,res,a[maxn];
struct BIT{
	int t[maxn];
	void update(int x,int k){
		for(int i=x;i<=n;i+=i&-i) t[i]+=k;
	}
	int query(int x){
		int res=0;
		for(int i=x;i;i-=i&-i) res+=t[i];
		return res;
	}
	void clear(){
		for(int i=1;i<=n;i++) t[i]=0;
	}
}T;
inline void solve(){
	cin>>C>>n>>k;
	T.clear();
	int res=0;
	for(int i=1,j=1;i<=n;i++) cin>>a[i];
	for(int i=n;i>=1;i--) res+=T.query(a[i]),T.update(a[i],1);
	T.clear();
	k=res-k;
	if(!k) return cout<<"0\n",void();
	res=k;
	for(int i=1,j=1;i<=n;i++){
		res-=i-j-T.query(a[i]);
		T.update(a[i],1);
		while(res<0) T.update(a[j],-1),res+=T.query(a[j]-1),j++;
		if(!res) return cout<<"1\n"<<j<<' '<<i<<'\n',void();
	}
	T.clear();
	res=0;
	cout<<"2\n";
	for(int i=1;i<=n;i++){
		int tmp=i-1-T.query(a[i]);
		T.update(a[i],1);
		res+=tmp;
		if(res<k) continue;
		cout<<"1 "<<i-1<<'\n';
		cout<<(i-(k-(res-tmp)))<<' '<<i<<'\n';
		return;
	}
	assert(0);
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	#endif
	ios::sync_with_stdio(0),cin.tie(0);
	// init();
	signed T=1;
	// scanf("%d",&T);
	// cin>>T;
	while(T--) solve();
	cerr<<"Time: "<<clock()*1000/CLOCKS_PER_SEC<<" ms\n";
	return 0;
}
/*
(j-p[i])/i>=k
*/ 
