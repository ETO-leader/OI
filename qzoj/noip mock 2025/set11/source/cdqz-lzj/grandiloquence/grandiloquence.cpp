#include<bits/stdc++.h>
using namespace std;
#define lc(x) tr[x].l
#define rc(x) tr[x].r
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
constexpr int N = 2e5+10;
constexpr int MAXK = 11;
constexpr int TREEBLOCK_REBUILD_LIM = 20000;
int n,m,K,fa[N],rt,DFN_CLOCK,mxdep;
int siz[N],rnk[N],dep[N];
mt19937_64 engine(time(0));
vector<int> G[N];
struct TreapNode{
	int val,siz,rsiz,tag,lazy,son[2];
	int cnt[MAXK];
};

inline int mmax(int a, int b){ return a>b?a:b; }

void predfs(int u, int pre){
	siz[u]=1,dep[u]=dep[pre]+1,rnk[++DFN_CLOCK]=u;
	mxdep=mmax(mxdep, dep[u]);
	for(int v:G[u]) predfs(v,u), siz[u]+=siz[v];
	return ;
}

struct TreeBlock{
	int B,tlt,a[N],lazy[N],cnt;
	int bottom[N],rnk[N],bel[N],nxt[N];
	vector<int> check_list[N];
	bool iskey[N];
	void add_to_checklist(int u, int add){
		check_list[u].pb(add); int cur = fa[u];
		while(!iskey[cur] && cur){
			check_list[cur].pb(add);
			cur = fa[cur];
		}
		return ;
	}
	void dfs(int u, int nxtkey){
		if(dep[u]==dep[nxtkey]+B || G[u].size()==0){
			nxt[u]=nxtkey; iskey[u]=1;
			bel[u]=++tlt,rnk[tlt]=u; lazy[tlt]=0;
			nxtkey=u;
			add_to_checklist(u,u);
		}
		for(int v:G[u]) dfs(v,nxtkey);
		return ;
	}
	int redfs(int u){
		int nearest = 0, news;
		for(int v:G[u]){
			news = redfs(v);
			if(!nearest || dep[news]<dep[nearest])
				nearest = news;
		}
		nearest = iskey[u] ? u : nearest;
		bottom[u] = nearest;
		return nearest;
	}
	void _pushdown(int idx){
		if(lazy[idx]==0) return ;
		int u=rnk[idx],cur=u;
		while(cur!=nxt[u])
			a[cur] += lazy[idx],
			cur = fa[cur];
		lazy[idx]=0;
		return ;
	}
	void rebuild(){
		for(int i=1;i<=tlt;i++) _pushdown(i);
		tlt=0;
		for(int i=1;i<=n;i++) check_list[i].clear();
		memset(iskey,0,sizeof iskey);
		memset(bottom,0,sizeof bottom);
		memset(rnk,0,sizeof rnk);
		memset(bel,0,sizeof bel);
		memset(nxt,0,sizeof nxt);
		mxdep=0;
		for(int i=1;i<=n;i++) mxdep=mmax(mxdep,dep[i]);
		B = (int)sqrt(mxdep); cnt = n / B + (n%B!=0);
		dfs(rt,0), redfs(rt);
		return ;
	}
	void addsize(int u, int v){
		int idx = bel[ bottom[u] ],cur=u;
		_pushdown(idx);
		while(cur!=nxt[bottom[u]])
			a[cur] += v, cur = fa[cur];
		while(cur)
			lazy[bel[cur]] += v, cur = nxt[cur];
		return ;
	}
	int query_exsize(int u){
		for(int v:check_list[u]) _pushdown(bel[v]);
		return a[u];
	}
	void insert(int parent, int u){
		bottom[u]=u;
		bel[u] = ++tlt, rnk[tlt] = u;
		iskey[u] = 1;
		nxt[u] = iskey[parent] ? parent : nxt[bottom[parent]];
		return ;
	}
	void balance(){
		if(B*cnt+TREEBLOCK_REBUILD_LIM <= n) rebuild();
		return ;
	}
} tb;

struct ChainBlock{
	int B,cnt,tmp[N],nn,bel[N],rnk[N];
	struct Block{
		int L,R;
		vector<int> vs;
	}blk[N];
	pii mtarget(int v){
		int cur=rnk[v];
		for(int i=0;i<blk[cur].vs.size();i++)
			if(blk[cur].vs[i]==v) return {cur,i};
	}
	int dfn(int u){
		pii res=mtarget(u);
		for(int i=1; i<res.fi; i++) res.se+=blk[i].vs.size();
		return res.se+1;
	}
	void pia(){
		memset(rnk,0,sizeof rnk);
		nn=0; for(int i=1;i<=cnt;i++){
			for(int v:blk[i].vs)tmp[++nn]=v,rnk[v]=i;
			blk[i].vs.clear();
		} cnt=0,B=0;
		return ;
	}
	void rebuild(){
		B = sqrt(nn), cnt = nn/B+(nn%B!=0);
		for(int i=1; i<=nn; i++){
			bel[i]=(i-1)/B+1;
			blk[bel[i]].L=(bel[i]-1)*B+1;
			blk[bel[i]].R=min(nn,bel[i]*B);
			blk[bel[i]].vs.pb(tmp[i]);
			rnk[tmp[i]] = bel[i];
		}
		return ;
	}
	void insert(int p, int v){
		int bl=1, pl=p;
		while(pl>blk[bl].vs.size()) pl-=blk[bl].vs.size(), bl++;
		blk[bl].vs.insert(blk[bl].vs.begin()+pl, v);
		nn++;
		rnk[v] = bl;
		if(blk[bl].vs.size() >= 2*B) pia(), rebuild();
		return ;
	}
} cb;

struct Treap{
	struct TreapNode{
		int val,pri,l,r,siz,rsiz,tag,cnt[MAXK];
		int lazy;
	} tr[N];
	int tlt,rt;
	void pushup(int POS){
		tr[POS].siz = tr[tr[POS].l].siz + tr[tr[POS].r].siz + 1;
		tr[POS].rsiz = tr[tr[POS].l].rsiz + tr[tr[POS].r].rsiz + tr[POS].tag;
		for(int k=1;k<=K;k++){
			tr[POS].cnt[k]=tr[lc(POS)].cnt[k] + tr[rc(POS)].cnt[k] + (tr[POS].tag==1 && tr[POS].val==k);
		}
		return ;
	}	
	void change(int POS, int c){
		tr[POS].lazy = c, tr[POS].val = c;
		for(int k=1; k<=K; k++){
			tr[POS].cnt[k] = (tr[POS].lazy==k) ? tr[POS].rsiz : 0;
		}
		return ;
	}
	void pushdown(int POS){
		if(!POS || !tr[POS].lazy) return ;
		if(tr[POS].l) change(lc(POS), tr[POS].lazy);
		if(tr[POS].r) change(rc(POS), tr[POS].lazy);
		tr[POS].lazy = 0;
		return ;
	}
	int newnode(int v, int tag){
		tr[++tlt].val=v;
		tr[tlt].pri=engine();
		tr[tlt].l=tr[tlt].r=0;
		tr[tlt].siz=1;
		tr[tlt].tag=tr[tlt].rsiz=tag;
		for(int k=1;k<=K;k++) tr[tlt].cnt[k]=(v==k);
		return tlt;
	}
	int merge(int x,int y){
		if(!x||!y) return x+y;
		if(tr[x].pri < tr[y].pri){
			pushdown(x);
			tr[x].r=merge(tr[x].r, y);
			pushup(x);
			return x;
		}
		else{
			pushdown(y);
			tr[y].l=merge(x, tr[y].l);
			pushup(y);
			return y;
		}
	}
	void split(int POS, int k, int &x, int &y){
		if(!POS){ x=y=0; return ; }
		pushdown(POS);
		if(tr[tr[POS].l].siz >= k)
			y=POS, split(tr[POS].l,k,x,tr[POS].l);
		else
			x=POS, split(tr[POS].r, k-tr[tr[POS].l].siz-1, tr[POS].r, y);
		pushup(POS);
		return ;
	}
}fhq[MAXK];

inline int nxt_r(int r){
	int v = (r+1)%K;
	return v;
}

inline int nxt_c(int c){
	int v = (c+1)%K;
	return v==0 ? K : v;
}

void Color(int u, int c){
	int l = cb.dfn(u), len = siz[u]+tb.query_exsize(u);
	int st = dep[u]%K;
	int r=st,x,y,z;
	do{
		fhq[r].split(fhq[r].rt, l-1, x, z);
		fhq[r].split(z, len, y, z);
		fhq[r].change(y, c);
		fhq[r].rt = fhq[r].merge(x, fhq[r].merge(y, z));
		r = nxt_r(r), c = nxt_c(c);
	}while(r!=st);
	return ;
}

int Query(int u, int c){
	int res=0, l = cb.dfn(u), len = siz[u]+tb.query_exsize(u);
	for(int r=0;r<K;r++){
		int x,y,z;
		fhq[r].split(fhq[r].rt, l-1, x, z);
		fhq[r].split(z, len, y, z);
		res += fhq[r].tr[y].cnt[c];
		fhq[r].rt = fhq[r].merge(fhq[r].merge(x,y), z);
	}
	return res;
}

void Insert(int u){
	int t = ++n, l = cb.dfn(u);
	fa[t] = u, G[u].pb(t), dep[t] = dep[u] + 1;  // 注意这里不会改变sizu
	cb.insert(cb.dfn(u), t);
	tb.insert(u, t);
	tb.addsize(t, 1);  // 到根路径上所有点的siz++
	tb.balance();
	int x,y;
	for(int r=0; r<K; r++){
		fhq[r].split(fhq[r].rt, l, x, y);
		fhq[r].rt = fhq[r].merge(fhq[r].merge(x, fhq[r].newnode(0, dep[t]%K==r) ), y);
	}
	return ;
}


signed main(){
	freopen("grandiloquence.in", "r", stdin);
	freopen("grandiloquence.out", "w", stdout);
	int tp;cin>>tp;
	cin >> n >> m >> K;
	for(int i=1; i<=n; i++){
		cin >> fa[i];
		if(!fa[i]) rt=i;
		G[fa[i]].pb(i);
	}
	predfs(rt,0);
	cb.nn=n;
	for(int i=1; i<=n; i++) cb.tmp[i] = rnk[i];
	cb.rebuild();
	tb.rebuild();
	for(int r=0; r<K; r++)
		for(int i=1; i<=n; i++) 
			fhq[r].rt=fhq[r].merge(fhq[r].rt, fhq[r].newnode(0, dep[rnk[i]]%K==r));
	int lstans=0;
	while(m--){
		int opt,u,c; cin >> opt;
		if(opt==1){
			cin >> u >> c; if(tp)u^=lstans, c^=lstans; Color(u,c);}
		else if(opt==2){
			cin >> u >> c; if(tp)u^=lstans, c^=lstans; printf("%d\n", lstans=Query(u,c));}
		else if(opt==3){
			cin >> u; if(tp)u^=lstans; Insert(u);}
	}
	return 0;
}
