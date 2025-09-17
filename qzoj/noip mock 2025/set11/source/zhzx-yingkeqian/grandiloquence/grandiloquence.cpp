#include<bits/stdc++.h>
#define maxn 250005
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
const int N=1145,Mod=998244353,L=2e6+10,inf=(int)1e9+7,Inv=(Mod+1)/2,FM=402653184,Blen=450,G=3,iG=(Mod+1)/G,V=1e9;
inline int reduce(int x){return x-(x>=Mod)*Mod;}
inline int reduce(int x,int Mod){return x-(x>=Mod)*Mod;}

int _C;
int n,m,k,fa[maxn];
namespace solve1{
	int cnt,dfn[maxn],siz[maxn],d[maxn],dep[maxn];
	vector<int>e[maxn];
	void dfs(int x,int lst){
		dfn[x]=++cnt,siz[x]=1;
		dep[x]=dep[lst]+1;
		d[dfn[x]]=d[dfn[lst]]+1;
		for(int i:e[x]){
			if(i==lst) continue;
			dfs(i,x);
			siz[x]+=siz[i];
		}
	}
	struct Sgt{
		struct node{
			int sum[11],ans[11],tg;
			node(){
				memset(sum,0,sizeof(sum));
				memset(ans,0,sizeof(ans));
				tg=-1;
			}
			void set(int x){
				tg=x;
				for(int i=0;i<k;i++) ans[(i+x)%k]=sum[i];
			}
		}s[maxn<<2];
		void pushup(int x){
			for(int i=0;i<k;i++) s[x].sum[i]=s[x<<1].sum[i]+s[x<<1|1].sum[i];
			for(int i=0;i<k;i++) s[x].ans[i]=s[x<<1].ans[i]+s[x<<1|1].ans[i];
		}
		void pushdown(int x){
			if(s[x].tg==-1) return;
			s[x<<1].set(s[x].tg);
			s[x<<1|1].set(s[x].tg);
			s[x].tg=-1;
		}
		void build(int x,int l,int r){
			if(l==r) return s[x].sum[d[l]%k]++,void();
			int mid=l+r>>1;
			build(x<<1,l,mid);
			build(x<<1|1,mid+1,r);
			pushup(x);
		}
		void update(int x,int l,int r,int sl,int sr,int k){
			if(sl<=l&&r<=sr) return s[x].set(k);
			int mid=l+r>>1;
			pushdown(x);
			if(sl<=mid) update(x<<1,l,mid,sl,sr,k);
			if(mid<sr) update(x<<1|1,mid+1,r,sl,sr,k);
			pushup(x);
		}
		void update(int x,int l,int r,int pos,int k){
			if(l==r) return s[x].sum[k]++,void();
			int mid=l+r>>1;
			pushdown(x);
			if(pos<=mid) update(x<<1,l,mid,pos,k);
			else update(x<<1|1,mid+1,r,pos,k);
			pushup(x);
		}
		int query(int x,int l,int r,int sl,int sr,int k){
			if(sl<=l&&r<=sr) return s[x].ans[k];
			int mid=l+r>>1,tmp=0;
			pushdown(x);
			if(sl<=mid) tmp=query(x<<1,l,mid,sl,sr,k);
			if(mid<sr) tmp+=query(x<<1|1,mid+1,r,sl,sr,k);
			return tmp;
		}
	}S;
	void solve(){
		int lst=0;
		for(int i=2;i<=n;i++) e[fa[i]].push_back(i);
		dfs(1,0);
		S.build(1,1,n);
		for(int i=1;i<=m;i++){
			int op;
			cin>>op;
			if(op==1){
				int u,c;
				cin>>u>>c;
				if(_C&1^1) u^=lst,c^=lst;
				c--;
				S.update(1,1,n,dfn[u],dfn[u]+siz[u]-1,(c+k-dep[u]%k)%k);
			}
			else if(op==2){
				int u,c;
				cin>>u>>c;
				if(_C&1^1) u^=lst,c^=lst;
				c--;
				cout<<(lst=S.query(1,1,n,dfn[u],dfn[u]+siz[u]-1,c))<<'\n';
			}
			else{
				int u;
				cin>>u;
				if(_C&1^1) u^=lst;
				if(u>n) continue;
				S.update(1,1,n,dfn[u],(dep[u]+1)%k);
			}
		}
	}
}
inline void solve(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>fa[i];
	solve1::solve();
	// if(_C&1) solve1::solve();
	// else solve2::solve();
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("grandiloquence.in","r",stdin);
	freopen("grandiloquence.out","w",stdout);
	#endif
	ios::sync_with_stdio(0),cin.tie(0);
	// init();
	signed T=1;
	// scanf("%d",&T);
	cin>>_C;
	while(T--) solve();
	cerr<<"Time: "<<clock()*1000/CLOCKS_PER_SEC<<" ms\n";
	return 0;
}
/*
(j-p[i])/i>=k
*/ 
