#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class sparsetable{
private:
    static constexpr auto ups=21;
    vector<vector<int>> mn;
    auto init(vector<int> a){
        const auto n=(int)(a.size());
        mn.resize(ups,vector<int>(n));
        mn[0]=a;
        cir(c,1,ups) cir(i,0,n-(1<<c)+1){
            mn[c][i]=min(mn[c-1][i],mn[c-1][i+(1<<(c-1))]);
        }
    }
public:
    auto query(int l,int r){
        const auto lg=__lg(r-l+1);
        return min(mn[lg][l],mn[lg][r-(1<<lg)+1]);
    }
    sparsetable(vector<int> a){init(a);}
};
class tree{
private:
    vector<vector<int>> gr,up;
    static constexpr auto ups=21;
    vector<int> dfn,rdfn,rt,pos,udfn,dep;
    sparsetable*st;
    auto dfs(int u,auto&c,int f=0)->void{
        dfn[u]=++c;dep[u]=dep[f]+1;
        udfn[c]=u;pos[u]=(int)(rt.size());
        up[0][u]=f;
        cir(i,1,ups) up[i][u]=up[i-1][up[i-1][u]];
        rt.emplace_back(dfn[u]);
        for(auto&i:gr[u]) if(i!=f) dfs(i,c,u),rt.emplace_back(dfn[u]);
        rdfn[u]=c;
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto init(){
        auto c=-1;
        dfs(0,c);
        st=new sparsetable(rt);
    }
    auto jump_until(int u,int dis){
        cir(i,0,ups) if(dis&(1<<i)) u=up[i][u];
        return u;
    }
    auto lca(int u,int v){
        return udfn[st->query(min(pos[u],pos[v]),max(pos[u],pos[v]))];
    }
    auto dist(int u,int v){
        return dep[u]+dep[v]-dep[lca(u,v)]*2;
    }
    tree(int _n):gr(_n),dfn(_n),rdfn(_n),udfn(_n),pos(_n),dep(_n),st(nullptr),up(ups,vector<int>(_n)){}
    ~tree(){if(st) delete st;}
    friend class virtual_tree;
};
class virtual_tree{
private:
    tree*tr;
    vector<int> anc,cnt,ux,ori,ctrl,uf;
    vector<vector<int>> vx;
    auto label(int u)->void{
        if(ori[u]) ctrl[u]=u;
        for(auto&i:vx[u]){
            label(i);
            if(ctrl[u]==-1) ctrl[u]=ctrl[i];
            else if(const auto ud=tr->dist(ctrl[u],u),vd=tr->dist(ctrl[i],u);ud>vd||ud==vd&&ctrl[u]>ctrl[i]) ctrl[u]=ctrl[i];
        }
    }
    auto relabel(int u,int f)->void{
        if(ctrl[u]==-1) ctrl[u]=ctrl[f];
        else if(const auto ud=tr->dist(ctrl[u],u),vd=tr->dist(ctrl[f],u);ud>vd||ud==vd&&ctrl[u]>ctrl[f]) ctrl[u]=ctrl[f];
        for(auto&i:vx[u]) relabel(i,u);
    }
public:
    auto build(vector<int> p){
        sort(p.begin(),p.end(),[&](auto a,auto b){return tr->dfn[a]<tr->dfn[b];});
        ux=p;
        cir(i,1,(int)(p.size())) ux.emplace_back(tr->lca(p[i-1],p[i]));
        sort(ux.begin(),ux.end());
        ux.erase(unique(ux.begin(),ux.end()),ux.end());
        sort(ux.begin(),ux.end(),[&](auto a,auto b){return tr->dfn[a]<tr->dfn[b];});
        stack<int,vector<int>> w;
        for(auto&i:ux){
            while((!w.empty())&&tr->rdfn[w.top()]<tr->dfn[i]) w.pop();
            if(!w.empty()) uf[i]=w.top(),vx[w.top()].emplace_back(i);
            w.emplace(i);
        }
        for(auto&x:p) ori[x]=true;
    }
    auto check(){
        const auto r=ux[0];
        label(r);
        relabel(r,r);
        cir(i,0,(int)(ux.size())){
            for(auto&x:vx[ux[i]]){
                const auto v=tr->jump_until(x,tr->dep[x]-tr->dep[ux[i]]-1);
                cnt[ctrl[ux[i]]]-=tr->rdfn[v]-tr->dfn[v]+1;
            }
            cnt[ctrl[ux[i]]]+=tr->rdfn[ux[i]]-tr->dfn[ux[i]]+1;
        }
        cnt[ctrl[r]]+=(int)(vx.size())-tr->rdfn[r]+tr->dfn[r]-1;
        cir(i,1,(int)(ux.size())){
            const auto u=ux[i];
            const auto f=uf[u];
            const auto ud=tr->dist(ctrl[u],u);
            const auto fd=tr->dist(ctrl[f],f);
            auto xd=tr->dist(u,f)-1;
            const auto p=tr->jump_until(u,xd);
            auto sp=0;
            if(ud>fd) xd-=ud-fd;
            if(fd>ud) xd-=fd-ud,sp+=fd-ud;
            sp+=xd/2;
            if(xd>0&&(xd&1)&&ctrl[u]<ctrl[f]) ++sp;
            const auto x=tr->jump_until(u,min(sp,tr->dist(u,f)-1));
            cnt[ctrl[u]]+=tr->rdfn[x]-tr->dfn[x]-tr->rdfn[u]+tr->dfn[u];
            cnt[ctrl[f]]+=tr->rdfn[p]-tr->dfn[p]-tr->rdfn[x]+tr->dfn[x];
        }
    }
    auto count(int u){return cnt[u];}
    auto clear(){
        for(auto&i:ux) anc[i]=0,ori[i]=false,vx[i].clear(),ctrl[i]=-1,uf[i]=-1,cnt[i]=0;
        ux.clear();
    }
    virtual_tree(tree&x,int _n):tr(&x),anc(_n),cnt(_n),vx(_n),uf(_n,-1),ori(_n),ctrl(_n,-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    tree tr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        tr.link(u,v);
    }
    tr.init();
    virtual_tree vt(tr,n);
    int q;cin>>q;
    cir(i,0,q){
        int c;cin>>c;
        vector<int> p(c);
        for(auto&x:p) cin>>x,--x;
        vt.build(p);
        vt.check();
        for(auto&i:p) cout<<vt.count(i)<<' ';
        cout<<'\n';
        vt.clear();
    }
    return 0;
}
