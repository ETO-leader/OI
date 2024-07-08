#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
class segment{
private:
    int _n;vector<T> val;
    void change(int u,int l,int r,int s,T v){
        if(l==s&&r==s){val[u]=v;return;}
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;
        mid<s?change(rs,mid+1,r,s,v):change(ls,l,mid,s,v);
        val[u]=val[ls]+val[rs];
    }
    T quary(int u,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr) return val[u];
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;
        T res=0;
        if(mid>=ql) res+=quary(ls,l,mid,ql,qr);
        if(mid<qr) res+=quary(rs,mid+1,r,ql,qr);
        return res;
    }
public:
    segment(int __n=0):_n(__n),val(__n*4){}
    void resize(int __n){(*this)=segment(__n);}
    void change(int s,T v){change(1,1,_n,s,v);}
    T quary(int l,int r){
        return quary(1,1,_n,min(l,r),max(l,r));}
};
using lint=long long;
segment<lint> seg;
struct edge{int v,eid;bool isheavy;};
vector<vector<edge>> G;
vector<int> Hvs,isl,F,H,ex;
vector<vector<int>> UP;
int HT;
int dfs(int u,int f=0){
    F[u]=f;UP[u][0]=f;H[u]=H[f]+1;
    cir(i,1,HT+1) UP[u][i]=UP[UP[u][i-1]][i-1];
	int mx=0,k=0,cnt=0,cx=1,lea=true;
	for(auto&i:G[u]){
        if(i.v==f){++cnt;continue;}
		ex[i.eid]=i.v;
        int d=dfs(i.v,u);
        if(d>mx) mx=d,k=cnt;
		cx+=d;lea=false;++cnt;
	}
    isl[u]=lea;Hvs[u]=k;
    if(isl[u]) return 1;
	return cx;
}
int lca(int u,int v){
    if(u==v) return u;
    if(H[u]<H[v]) swap(u,v);
    cir(i,0,HT) if((1<<i)&(H[u]-H[v])) u=UP[u][i];
    if(u==v) return u;
    for(int i=HT;~i;--i) if(UP[u][i]!=UP[v][i])
        u=UP[u][i],v=UP[v][i];
    return UP[u][0];
}
vector<int> id,Rt;
int idcnt=0;
void spirt(int u,int f=0,int rt=1){
	int cnt=0;
	id[u]=++idcnt;Rt[u]=rt;
    if(isl[u]) return;
	G[u][Hvs[u]].isheavy=true;
	spirt(G[u][Hvs[u]].v,u,rt);
	for(auto&i:G[u]){
		if(cnt!=Hvs[u]&&i.v!=f) spirt(i.v,u,i.v);
        ++cnt;
	}
}
lint jump(int k,int l){
    lint res=0;
	while(Rt[k]!=Rt[l]){
		res+=seg.quary(id[k],id[Rt[k]]);
        k=F[Rt[k]];
    }
    res+=seg.quary(id[k],id[l]);
    return res;
}
lint runans(int x,int y){
    const int l=lca(x,y);
    return jump(x,l)+jump(y,l)-seg.quary(id[l],id[l])*2;
}
void reset(int eid,lint w){
    seg.change(id[ex[eid-1]],w);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<lint> wi(n-1);
    [&](){
        seg.resize(n+1);G.resize(n+1);Rt.resize(n+1);
        Hvs.resize(n+1);id.resize(n+1);isl.resize(n+1);
        H.resize(n+1);F.resize(n+1);HT=log2(n)+2;
        ex.resize(n-1);
        UP.assign(n+1,vector<int>(HT+1));
    }();
    cir(i,0,n-1){
        int u,v;cin>>u>>v>>wi[i];
        G[u].push_back({v,i,false});
        G[v].push_back({u,i,false});
    }
    dfs(1);spirt(1);
    cir(i,0,n-1) reset(i+1,wi[i]);
    int q;cin>>q;
    cir(i,0,q){
        lint op,a,b;cin>>op>>a>>b;
        if(op==1) reset(a,b);
        else cout<<runans(a,b)<<'\n';
    }
    return 0;
}