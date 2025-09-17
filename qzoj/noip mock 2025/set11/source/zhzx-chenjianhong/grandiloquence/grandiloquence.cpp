#include<bits/stdc++.h>
#define forUp(i,a,b) for(int i=(a);i<=(b);++i)
#define forUP(i,a,b) for(int i=(a);i<(b);++i)
#define forDown(i,a,b) for(int i=(a);i>=(b);--i)
#define forG(u,v) for(int __i=head[u],v=to[__i];__i;__i=nxt[__i],v=to[__i])
#define forWG(u,v,c) for(int __i=head[u],v=to[__i],c=w[__i];__i;__i=nxt[__i],v=to[__i],c=w[__i])
#define pb push_back
bool __mst;using ll=long long;using ull=unsigned long long;using uint=unsigned int;using db=double;using ld=long db;using pii=std::pair<int,int>;using pdi=std::pair<db,int>;using vl=__int128;using uvl=unsigned __int128;
constexpr int INF=0x3f3f3f3f,MINF=0xcfcfcfcf;constexpr long long INFLL=0x3f3f3f3f3f3f3f3f,MINFLL=0xcfcfcfcfcfcfcfcf;constexpr double INFDB=1e50,eps=1e-4;
template<class _Tp>void chkMax(_Tp &x,const _Tp &y){x<y?x=y:0;}template<class _Tp>void chkMin(_Tp &x,const _Tp &y){x>y?x=y:0;}
constexpr int N=4e5+10;int __test_num=1,__task_id;using namespace std;void __init();

int n,k,tot,q,op,u,c,fa[N],col[N],lst;

int cnt,head[N],to[N<<1],nxt[N<<1];
void addEdge(int u,int v){
	++cnt,to[cnt]=v,nxt[cnt]=head[u],head[u]=cnt;
}

void dfs1(int rt,int fa,int c){
	col[rt]=c;
	forG(rt,son)if(son!=fa)dfs1(son,rt,c%k+1);
}
int dfs2(int rt,int fa,int c){
	int ans=0;
	if(col[rt]==c)++ans;
	forG(rt,son)if(son!=fa)ans+=dfs2(son,rt,c);
	return ans;
}

bool __med;void __solve(int __test_id){
	cin>>n>>q>>k;tot=n;
	forUp(son,1,n){
		cin>>fa[son];
		if(fa[son])addEdge(fa[son],son);
	}
	while(q--){
		cin>>op>>u;u^=lst*((__task_id&1)^1);
		if(op==1)cin>>c,c^=lst*((__task_id&1)^1),dfs1(u,fa[u],c);
		if(op==2)cin>>c,c^=lst*((__task_id&1)^1),cout<<(lst=dfs2(u,fa[u],c))<<'\n';
		if(op==3)fa[++tot]=u,addEdge(fa[tot],tot);
	}
}
signed main(){
	__init();
	forUp(i,1,__test_num)__solve(i);
	return 0;
}
void __init(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	const string __file_name="grandiloquence";freopen((__file_name+".in").c_str(),"r",stdin);freopen((__file_name+".out").c_str(),"w",stdout);
	//cerr<<((&__mst)-(&__med))/1024.0/1024.0<<"MB"<<endl;
	//scanf("%d",&__test_num);
	//cin>>__test_num;
	cin>>__task_id;
}
