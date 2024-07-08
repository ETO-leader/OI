#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define rsz(x) (x).resize(n+1)
using namespace std;
template<typename T>
class segment{
private:
    int _n;vector<T> val;
    T change(int u,int l,int r,int s,int v){
        if(l==s&&r==s){val[u]=v;return val[u];}
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;
        val[u]=max((mid<s?change(rs,mid+1,r,s,v):
            change(ls,l,mid,s,v)),(mid<s?val[ls]:val[rs]));
        return val[u];
    }
    T quary(int u,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr) return val[u];
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;T res=0;
        if(mid>=ql) res=max(quary(ls,l,mid,ql,qr),res);
        if(mid<qr) res=max(quary(rs,mid+1,r,ql,qr),res);
        return res;
    }
public:
    segment(int __n=0):_n(__n),val(__n*4){}
    void resize(int __n){(*this)=segment(__n);}
    void change(int s,int v){change(1,1,_n,s,v);}
    T quary(int l,int r){return quary(1,1,_n,min(l,r),max(l,r));}
};
using lint=long long;
segment<lint> seg;
struct edge{int v;lint w;bool isheavy;};
vector<vector<edge>> G;
vector<int> Hvs,isl,F,H;
vector<vector<int>> UP;
vector<lint> Hx;
int HT;
int dfs(int u,int f=0){
    F[u]=f;UP[u][0]=f;H[u]=H[f]+1;
    cir(i,1,HT+1) UP[u][i]=UP[UP[u][i-1]][i-1];
	int mx=0,k=0,cnt=0,cx=1,lea=true;
	for(auto&i:G[u]){
        if(i.v==f){++cnt;continue;}
        Hx[i.v]=Hx[u]+i.w;
		int d=dfs(i.v,u);if(d>mx) mx=d,k=cnt;
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
lint jump(int k,int l){
    lint res=0;
	while(Rt[k]!=Rt[l]){
		res=max(seg.quary(id[k],id[Rt[k]]),res);
        k=F[Rt[k]];
    }
    res=max(seg.quary(id[k],id[l]),res);
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<int> v(n+1);
    rsz(seg);rsz(G);rsz(Rt);rsz(Hvs);rsz(id);rsz(isl);
    rsz(H);rsz(F);HT=log2(n)+2;rsz(Hx);
    UP.assign(n+1,vector<int>(HT+1));
    cir(i,1,n+1) cin>>v[i];
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w,false}),G[v].push_back({u,w,false});
    }
    dfs(1);split(1);
    cir(i,1,n+1) seg.change(id[i],v[i]);
    cir(i,0,q){
        int k,v;cin>>k>>v;
        int l=lca(k,v);
        cout<<Hx[k]+Hx[v]-Hx[l]*2<<' '<<max(jump(k,l),jump(v,l))<<'\n';
    }
    cout<<'\n';
    return 0;
}