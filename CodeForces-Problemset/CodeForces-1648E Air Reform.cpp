#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
class dsu{
private:
    VI f;
public:
    int findset(int u){
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    void merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    bool is_root(int u){return u==findset(u);}
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
struct edge_t{int u,v,w;};
class graph{
private:
    vector<VI> G,up;
    VI w,dfn,hx;
    int n,__lg2,fcnx,root;
    void dfs(int u){
        hx[u]=hx[up[u][0]]+1;
        if(u<n+1) dfn[u]=++fcnx;
        cir(i,1,__lg2) up[u][i]=up[up[u][i-1]][i-1];
        for(auto&i:G[u]) dfs(i);
    }
    int lca(int u,int v) const{
        if(hx[u]<hx[v]) swap(u,v);
        cir(i,0,__lg2) if((hx[u]-hx[v])&(1<<i))
            u=up[u][i];
        for(int i=__lg2-1;~i;--i) if(up[u][i]!=up[v][i])
            u=up[u][i],v=up[v][i];
        return up[u][0];
    }
    #define dfncmp(x) [&](int a,int b){\
        return x.dfn[a]<x.dfn[b];}
public:
    void kruskal(vector<edge_t> es){
        dsu ds(n+1);
        sort(es.begin(),es.end(),[&](edge_t&a,edge_t&b){
            return a.w<b.w;});
        int cnx=n;VI rt(n+1);
        iota(rt.begin(),rt.end(),0);
        for(auto&[u,v,wx]:es){
            u=ds.findset(u);v=ds.findset(v);
            if(u==v) continue;
            w[++cnx]=wx;
            G[cnx].push_back(rt[u]);
            G[cnx].push_back(rt[v]);
            up[rt[u]][0]=cnx;up[rt[v]][0]=cnx;
            rt[u]=cnx;rt[v]=cnx;
            ds.merge(u,v);
        }
        dfs(root);
    }
    void boruvka(const graph&gx,vector<edge_t> gi){
        dsu ds(n+1);
        vector<VI> gxi(n+1);
        for(auto&[u,v,w]:gi)
            gxi[u].push_back(v),gxi[v].push_back(u);
        vector<VI::iterator> ia(n+1),ib(n+1);
        VI fp(n+1),np(n+1),idx(n+1),lx(n*2),rx(n*2);
        cir(i,1,n+1){
            sort(gxi[i].begin(),gxi[i].end(),dfncmp(gx));
            ia[i]=ib[i]=lower_bound(gxi[i].begin(),
                gxi[i].end(),i,dfncmp(gx));
            ia[i]-=(ia[i]!=gxi[i].begin());
            fp[i]=gx.dfn[i],np[i]=gx.dfn[i];
            idx[gx.dfn[i]]=i;
        }
        vector<edge_t> exi;
        while(exi.size()<n-1){
            cir(l,1,n+1){
                int r=l;
                for(;r<n+1&&ds.findset(idx[l])
                    ==ds.findset(idx[r]);++r);
                cir(i,l,r) lx[i]=l,rx[i]=r-1;
                l=r-1;
            }
            VI mn(n+1,_inf),mx(n+1,-1),my(n+1,-1);
            cir(i,1,n+1){
                while(fp[i]){
                    if(ds.findset(idx[fp[i]])==ds.findset(i)){
                        fp[i]=lx[fp[i]]-1;continue;
                    }
                    while(ia[i]!=gxi[i].begin()&&
                        gx.dfn[*ia[i]]>fp[i]) --ia[i];
                    if(gx.dfn[*ia[i]]==fp[i]) --fp[i];
                    else break;
                }
                while(np[i]<=n){
                    if(ds.findset(idx[np[i]])==ds.findset(i)){
                        np[i]=rx[np[i]]+1;continue;
                    }
                    while(ib[i]!=gxi[i].end()&&
                        gx.dfn[*ib[i]]<np[i]) ++ib[i];
                    if(ib[i]!=gxi[i].end()&&gx.dfn[*ib[i]]==np[i]){
                        ++np[i];
                    }else{
                        break;
                    }
                }
                int mni=_inf,wp=-1;
                auto calc_i=[&](int&x){
                    const int wi=gx.dist(idx[x],i);
                    if(wi<mni) mni=wi,wp=idx[x];
                };
                if(fp[i]) calc_i(fp[i]);
                if(np[i]<n+1) calc_i(np[i]);
                if(mni<mn[ds.findset(i)]){
                    assert(wp>0);
                    const int set_i=ds.findset(i);
                    mn[set_i]=mni;mx[set_i]=i;my[set_i]=wp;
                }
            }
            cir(i,1,n+1) if(ds.is_root(i)){
                const int nxp=ds.findset(my[i]);
                if(i==nxp) continue;
                ds.merge(i,nxp);
                exi.push_back({mx[i],my[i],mn[i]});
            }
        }
        kruskal(exi);
    }
    #undef dfncmp
    int dist(int u,int v) const{return w[lca(u,v)];}
    graph(int _n):n(_n),fcnx(0){
        const int nx=_n*2;root=nx-1;
        G.resize(nx);__lg2=log2(nx)+2;
        up.assign(nx,VI(__lg2));w.resize(nx);
        dfn.resize(nx);hx.resize(nx);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m;cin>>n>>m;vector<edge_t> es(m);
        for(auto&[u,v,w]:es) cin>>u>>v>>w;
        graph sg(n),fg(n);
        sg.kruskal(es);
        fg.boruvka(sg,es);
        for(auto&[u,v,w]:es)
            cout<<fg.dist(u,v)<<' ';
        cout<<'\n';
    }
    return 0;
}
