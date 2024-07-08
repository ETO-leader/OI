#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
class segment{
private:
    int _n;vector<T> val,tag;
    void push_down(int u){
        auto ls=u*2,rs=u*2+1;
        tag[ls]+=tag[u];tag[rs]+=tag[u];tag[u]=0;
    }
    T add(int u,int l,int r,int ql,int qr,T v){
        if(ql<=l&&r<=qr){
            tag[u]+=v;val[u]+=(r-l+1)*v;
            return (r-l+1)*v;
        }
        push_down(u);
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;T res=0;
        if(mid>=ql) res+=add(ls,l,mid,ql,qr,v);
        if(mid<qr) res+=add(rs,mid+1,r,ql,qr,v);
        val[u]+=res;
        return res;
    }
    T quary(int u,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr) return val[u];
        val[u]+=(r-l+1)*tag[u];push_down(u);
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;T res=0;
        if(mid>=ql) res+=quary(ls,l,mid,ql,qr);
        if(mid<qr) res+=quary(rs,mid+1,r,ql,qr);
        return res;
    }
public:
    segment(int __n=0):_n(__n),val(__n*4),tag(__n*4){}
    void resize(int __n){(*this)=segment(__n);}
    void add(int l,int r,int v){add(1,1,_n,min(l,r),max(l,r),v);}
    T quary(int l,int r){return quary(1,1,_n,min(l,r),max(l,r));}
};
using lint=long long;
segment<lint> seg;
struct edge{int v;bool isheavy;};
vector<vector<edge>> G;
vector<int> Hvs,isl,F;
int dfs(int u,int f=0){
    F[u]=f;
	int mx=0,k=0,cnt=0,cx=1,lea=true;
	for(auto&i:G[u]){
        if(i.v==f){++cnt;continue;}
		int d=dfs(i.v,u);if(d>mx) mx=d,k=cnt;
		cx+=d;lea=false;++cnt;
	}
    isl[u]=lea;Hvs[u]=k;
    if(isl[u]) return 1;
	return cx;
}
vector<int> id,Rt;
int IdCnt=0;
void split(int u,int f=0,int rt=1){
	int cnt=0;
	id[u]=++IdCnt;Rt[u]=rt;
    if(isl[u]) return;
	G[u][Hvs[u]].isheavy=true;
	split(G[u][Hvs[u]].v,u,rt);
	for(auto&i:G[u]){
		if(cnt!=Hvs[u]&&i.v!=f) split(i.v,u,i.v);
        ++cnt;
	}
}
lint jump(int k){
    lint res=0;
	while(k){
		res+=seg.quary(id[k],id[Rt[k]]);
        k=F[Rt[k]];
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<int> v(n+1);
    seg.resize(n+1);G.resize(n+1);Rt.resize(n+1);
    Hvs.resize(n+1);id.resize(n+1);isl.resize(n+1);
    F.resize(n+1);
    cir(i,1,n+1) cin>>v[i];
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back({v,false}),G[v].push_back({u,false});
    }
    dfs(1);split(1);
    cir(i,1,n+1) seg.add(id[i],id[i],v[i]);
    cir(i,0,q){
        int op,k,v;cin>>op>>k;
        if(op-1){
            cout<<jump(k)<<'\n';
        }else{
            cin>>v;seg.add(id[k],id[k],
                v-seg.quary(id[k],id[k]));
        }
    }
    return 0;
}