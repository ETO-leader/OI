#pragma GCC optimize(3)
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,abm,mmx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
#define cir(i,a,b) for(unsigned i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<unsigned>;
vector<unsigned> log2x;
template<typename _Ty>
class extend_vector{
private:
    vector<_Ty> a,f;
    auto rebuild(){
        if((f.size()<<3)<a.size()){
            sort(f.begin(),f.end());
            vector<_Ty> res(a.size()+f.size());
            merge(a.begin(),a.end(),f.begin(),f.end(),res.begin());
            a=res;
        }else{
            for(auto&i:f) a.push_back(i);
            sort(a.begin(),a.end());
        }
        f.clear();
    }
public:
    auto push_back(_Ty x){
        f.push_back(x);
        if(f.size()>log2x[a.size()]*23) rebuild();
    }
    auto order_of_key(_Ty x){
        auto resa=lower_bound(a.begin(),
            a.end(),x)-a.begin();
        for(auto&i:f) resa+=(i<x);
        return resa;
    }
    auto remove(_Ty x){
        if(a.size()<30000){
            auto lb=lower_bound(a.begin(),a.end(),x);
            if(lb!=a.end()&&(*lb)==x)
                return a.erase(lb),void();
            f.erase(find(f.begin(),f.end(),x));
        }else{
            if(count(f.begin(),f.end(),x))
                return f.erase(find(f.begin(),f.end(),x)),void();
            a.erase(lower_bound(a.begin(),a.end(),x));
        }
    }
    auto size(){
        return a.size()+f.size();
    }
    auto clear(){a.clear();f.clear();}
};
// unsigned
class graph{
private:
    static constexpr auto alphah=6;
    static constexpr auto ups=21;
    static constexpr int _n=1e5+7;
    struct edge{unsigned v,w;};
    array<vector<edge>,_n> gr;
    vector<VI> up;
    array<VI,_n> dtr;
    array<extend_vector<int>,_n> usiz,fsiz;
    array<unsigned,_n> siz,use,fx,wx,val,maxh,h;
    VI recycle;
    auto dfssz(unsigned u,unsigned f=0){
        if(use[u]) return siz[u]=0;
        siz[u]=1;
        for(auto&[v,w]:gr[u]) if(v!=f) siz[u]+=dfssz(v,u);
        return siz[u];
    }
    auto dfsrt(unsigned u,const unsigned sizu,unsigned f=0)->unsigned{
        unsigned res=0,mx=0,lst=sizu-1;
        if(use[u]) return res;
        for(auto&[v,w]:gr[u]) if(v!=f){
            res|=dfsrt(v,sizu,u);
            mx=max<unsigned>(mx,siz[v]);lst-=siz[v];
        }
        if(max(mx,lst)<sizu/2+1) return u;
        return res;
    }
    auto build(unsigned u,unsigned f=0)->unsigned{
        auto sizu=dfssz(u);
        auto rtu=dfsrt(u,sizu);
        dtr[f].push_back(rtu);
        fx[rtu]=f;use[rtu]=true;
        for(auto&[v,w]:gr[rtu]) if(!use[v]) build(v,rtu);
        return rtu;
    }
    auto lca(unsigned u,unsigned v)->unsigned{
        if(h[u]<h[v]) swap(u,v);
        cir(i,0,ups) if((h[u]-h[v])&(1<<i))
            u=up[i][u];
        if(u==v) return u;
        for(int i=ups-1;~i;--i) if(up[i][u]!=up[i][v])
            u=up[i][u],v=up[i][v];
        return up[0][u];
    }
    auto dist(unsigned u,unsigned v){
        return wx[u]+wx[v]-wx[lca(u,v)]*2;
    }
    auto __update(unsigned u,int w){
        val[u]=w;
        const auto fr=u;auto lasu=0;
        while(u){
            usiz[u].push_back((int)(dist(fr,u))-w);
            if(lasu) fsiz[lasu].push_back((int)(dist(fr,u))-w);
            lasu=u;u=fx[u];
        }
    }
    auto __remove(unsigned u,int w){
        const auto fr=u;auto lasu=0;
        while(u){
            usiz[u].remove((int)(dist(fr,u))-w);
            if(lasu) fsiz[lasu].remove((int)(dist(fr,u))-w);
            lasu=u;u=fx[u];
        }
    }
    auto getnodes(unsigned u)->void{
        if(val[u]) __remove(u,val[u]);
        for(auto&i:dtr[u]) getnodes(i);
        use[u]=false;recycle.push_back(u);
        usiz[u].clear();fsiz[u].clear();
        dtr[u].clear();
    }
    auto init(unsigned u)->int{
        maxh[u]=1;
        for(auto&i:dtr[u])
            maxh[u]=max<unsigned>(maxh[u],init(i)+1);
        return maxh[u];
    }
    auto rebuild(unsigned u){
        recycle.clear();
        getnodes(u);
        dtr[fx[u]].erase(find(dtr[fx[u]].begin(),
            dtr[fx[u]].end(),u));
        auto res=build(u,fx[u]);
        for(auto&i:recycle) if(val[i]) __update(i,val[i]);
        init(res);
        return res;
    }
public:
    auto link(unsigned u,unsigned v,unsigned wk){
        fx[v]=u;use[v]=true;
        dtr[u].push_back(v);
        wx[v]=wx[u]+wk;up[0][v]=u;h[v]=h[u]+1;
        cir(i,1,ups) up[i][v]=up[i-1][up[i-1][v]];
        int cntx=0;
        const auto fr=u;
        while(u=fx[u]) maxh[u]=max<unsigned>(maxh[u],++cntx);
        u=fr;
        if(u){
            gr[u].push_back({v,wk});
            gr[v].push_back({u,wk});
        }
        while(u=fx[u]) if(log2x[usiz[u].size()]*alphah<maxh[u]){
            rebuild(u);break;
        }
    }
    auto update(unsigned u,int w){__update(u,w);}
    auto query(unsigned u){
        const auto fr=u;
        auto lasu=0,cnt=0;
        while(u){
            const auto wi=val[fr]-dist(u,fr);
            cnt+=usiz[u].order_of_key(wi+1);
            if(lasu) cnt-=fsiz[lasu].order_of_key(wi+1);
            lasu=u;u=fx[u];
        }
        return cnt;
    }
    graph():/*gr(_n),*/up(ups,VI(_n))/*,usiz(_n),
        fsiz(_n),siz(_n),use(_n),fx(_n),wx(_n),
        val(_n),h(_n),maxh(_n),dtr(_n)*/{
        log2x.resize(_n);
        cir(i,0,ups) if((1<<i)<_n) log2x[1<<i]=i;
        cir(i,1,_n) log2x[i]=max(log2x[i-1],log2x[i]);
    }
} gr;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    unsigned testcaseid;cin>>testcaseid;
    unsigned n;cin>>n;
    lint ans=0;//graph gr(n+7);
    cir(i,0,n){
        unsigned u,wk,w;cin>>u>>wk>>w;
        u^=(ans%(unsigned)(1e9));
        gr.link(u,i+1,wk);gr.update(i+1,w);
        ans+=gr.query(i+1)-1;
        cout<<ans<<'\n';
    }
    return 0;
}
