#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
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
    vector<vector<pair<int,int>>> gr;
    vector<int> dfn,rt,pos,udfn,dep;
    vector<lint> vdep;
    sparsetable*st;
    auto dfs(int u,auto&c,int f=0)->void{
        dfn[u]=++c;dep[u]=dep[f]+1;
        udfn[c]=u;pos[u]=(int)(rt.size());
        rt.emplace_back(dfn[u]);
        for(auto&[v,w]:gr[u]) if(v!=f) vdep[v]=vdep[u]+w,dfs(v,c,u),rt.emplace_back(dfn[u]);
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto init(){
        auto c=-1;
        dfs(0,c);
        st=new sparsetable(rt);
    }
    auto lca(int u,int v){
        return udfn[st->query(min(pos[u],pos[v]),max(pos[u],pos[v]))];
    }
    auto distd(int u,int v){
        clog<<"D "<<u<<' '<<v<<' '<<lca(u,v)<<' '<<vdep[u]<<' '<<vdep[v]<<' '<<vdep[lca(u,v)]<<" = "<<vdep[u]+vdep[v]-vdep[lca(u,v)]*2<<'\n';
        return vdep[u]+vdep[v]-vdep[lca(u,v)]*2;
    }
    tree(int _n):gr(_n),dfn(_n),udfn(_n),pos(_n),dep(_n),vdep(_n),st(nullptr){}
    ~tree(){if(st) delete st;}
    friend class virtual_tree;
};
class virtual_tree{
private:
    tree*tr;
    set<int> px;
    lint sum;
public:
    auto emplace(int u){
        const auto ud=tr->dfn[u];
        const auto p=px.emplace(ud).first;
        if(p!=px.begin()&&next(p)!=px.end()) sum-=tr->distd(tr->udfn[*prev(p)],tr->udfn[*next(p)]);
        if(p!=px.begin()) sum+=tr->distd(tr->udfn[*prev(p)],tr->udfn[*p]);
        if(next(p)!=px.end()) sum+=tr->distd(tr->udfn[*p],tr->udfn[*next(p)]);
    }
    auto extract(int u){
        const auto ud=tr->dfn[u];
        const auto p=px.find(ud);
        if(p!=px.begin()) sum-=tr->distd(tr->udfn[*prev(p)],tr->udfn[*p]);
        if(next(p)!=px.end()) sum-=tr->distd(tr->udfn[*p],tr->udfn[*next(p)]);
        if(p!=px.begin()&&next(p)!=px.end()) sum+=tr->distd(tr->udfn[*prev(p)],tr->udfn[*next(p)]);
        px.erase(ud);
    }
    auto calc(){
        return sum+(px.size()>1?tr->distd(tr->udfn[*px.begin()],tr->udfn[*px.rbegin()]):0);
    }
    virtual_tree(tree&x):tr(&x),sum(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    tree tr(n);
    cir(i,0,n-1){
        int u,v;lint w;cin>>u>>v>>w;--u;--v;
        tr.link(u,v,w);
    }
    tr.init();
    virtual_tree vt(tr);
    vector<int> st(n);
    cir(i,0,q){
        int x;cin>>x;--x;
        if(st[x]) vt.extract(x);
        else vt.emplace(x);
        st[x]^=true;
        cout<<vt.calc()<<'\n';
    }
    return 0;
}
