#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
private:
    vector<lint> fct,ifct;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        for(auto&x:ifct) x=inv(x);
    }
    constexpr auto C(auto a,auto b) const{
        return a>b-1&&b>-1?fct[a]*ifct[b]%MOD*ifct[a-b]%MOD:0;
    }
} math;
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
    vector<vector<int>> gr;
    vector<int> dfn,rdfn,rt,pos,udfn;
    sparsetable*st;
    auto dfs(int u,auto&c,int f=0)->void{
        dfn[u]=++c;
        udfn[c]=u;pos[u]=(int)(rt.size());
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
    auto lca(int u,int v){
        return udfn[st->query(min(pos[u],pos[v]),max(pos[u],pos[v]))];
    };
    tree(int _n):gr(_n),dfn(_n),rdfn(_n),udfn(_n),pos(_n),st(nullptr){}
    ~tree(){if(st) delete st;}
    friend class virtual_tree;
};
class virtual_tree{
private:
    tree*tr;
    vector<int> anc,f,ux,ori;
    vector<vector<int>> vx;
    stack<int,vector<int>> w;
    vector<unordered_map<int,int>> lc;
public:
    auto build(vector<int> p,int r){
        sort(p.begin(),p.end(),[&](auto a,auto b){return tr->dfn[a]<tr->dfn[b];});
        ux=p;
        cir(i,1,(int)(p.size())) ux.emplace_back(tr->lca(p[i-1],p[i]));
        sort(ux.begin(),ux.end());
        ux.erase(unique(ux.begin(),ux.end()),ux.end());
        sort(ux.begin(),ux.end(),[&](auto a,auto b){return tr->dfn[a]<tr->dfn[b];});
        for(auto&i:ux){
            while((!w.empty())&&tr->rdfn[w.top()]<tr->dfn[i]) w.pop();
            if(!w.empty()) vx[i].emplace_back(w.top()),vx[w.top()].emplace_back(i);
            w.emplace(i);
        }
        while(!w.empty()) w.pop();
        auto dfs=[&](auto __self,int u,int f)->void {
            anc[u]=f;
            for(auto&x:vx[u]) if(x!=f) __self(__self,x,u);
        };
        dfs(dfs,r,r);
        for(auto&i:p) ori[i]=true;
        auto uf=[&](auto __self,int u){
            if(f[u]>-1) return f[u];
            auto res=ori[u];
            if(u!=r) res+=__self(__self,anc[u]);
            return f[u]=res;
        };
        for(auto&x:ux) uf(uf,x);
    }
    auto count(int u){return f[u];}
    auto clear(){
        for(auto&i:ux) anc[i]=0,f[i]=-1,ori[i]=false,vx[i].clear();
        ux.clear();
    }
    virtual_tree(tree&x,int _n):tr(&x),anc(_n),f(_n,-1),vx(_n),ori(_n),lc(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree tr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        tr.link(u,v);
    }
    tr.init();
    int q,m;cin>>q>>m;
    vector<lint> b(n+7,1);
    cir(i,1,n+7) b[i]=b[i-1]*(m-i+1)%MOD*math.inv(i)%MOD;
    math.init(n+7);
    virtual_tree vtr(tr,n);
    unordered_map<int,int> w;
    cir(i,0,q) [&]{
        int x,y;cin>>x>>y;
        vector<int> pl;
        for(auto w=x-1;w<n;w+=x) pl.emplace_back(w);
        if(y>(int)(pl.size())) return cout<<0<<'\n',void();
        vtr.build(pl,pl[i%(int)(pl.size())]);
        w.clear();
        for(auto&x:pl) ++w[vtr.count(x)];
        vtr.clear();
        auto ans=0ll;
        cir(c,0,y){
            auto uans=1ll;
            for(auto&[v,z]:w) (uans*=math.qpow(max(y-c-v+1,0),z))%=MOD;
            if(!uans) break;
            (ans+=uans*math.C(y,c)%MOD*((c&1)?MOD-1:1))%=MOD;
        }
        cout<<ans*b[y]%MOD<<'\n';
    }();
    return 0;
}
