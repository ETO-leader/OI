#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,abm,mmx")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4")
#pragma GCC target("tune=native")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("upsolving.in");
ofstream fcout("upsolving.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
using VI=vector<int>;
template<typename T>
class sparsetable{
private:
    vector<vector<T>> st;
    vector<int> lg2;
    int ht;
    void init(const vector<T>&v){
        int n=v.size();ht=log2(n)+2;
        st.assign(ht,vector<T>(n));
        lg2.resize(1<<ht);
        cir(i,0,ht) cir(j,(1<<i),(1<<(i+1))) lg2[j]=i;
        cir(i,0,n) st[0][i]=v[i];
        cir(j,1,ht) cir(i,0,(n-(1<<(j-1))))
            st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
    }
public:
    T operator()(int l,int r) const{
        int lg=lg2[r-l+1];
        return min(st[lg][l],st[lg][r-(1<<lg)+1]);
    }
    void registers(vector<T>&v){init(v);}
    sparsetable(const vector<T>&v){init(v);}
    sparsetable(){}
};
struct nodeqry{
    int h,u;
    bool operator<(const nodeqry&x) const{
        return h<x.h;
    }
};
vector<VI> G;
VI h,dfn,rdfn,inid;
vector<lint> dis,w;
vector<nodeqry> nq;
sparsetable<nodeqry> sq;
void dfs(int u,int&dcnt,int f=0){
    h[u]=h[f]+1;dis[u]=dis[f]+w[u];
    rdfn[dfn[u]=++dcnt]=u;
    nq.push_back({h[u],u});
    inid[u]=nq.size()-1;
    for(auto&i:G[u]) if(i!=f){
        dfs(i,dcnt,u);
        nq.push_back({h[u],u});
    }
}
int lca(int u,int v){
    if(inid[u]>inid[v]) swap(u,v);
    return sq(inid[u],inid[v]).u;
}
auto getans(int u,int v){
    u=rdfn[u];v=rdfn[v];
    return dis[v]-dis[lca(u,v)];
}
class solver{
private:
    set<int> slv;lint ans;
public:
    void insert(int u){
        auto ins=slv.insert(dfn[u]).first;
        if(slv.size()<2) return;
        if(ins==(--slv.end())){
            ans+=getans(*(--ins),dfn[u]);
            return;
        }
        auto l=ins,r=ins;--l;++r;
        ans-=getans(*l,*r);
        ans+=getans(*l,*ins);
        ans+=getans(*ins,*r);
    }
    void extract(int u){
        auto fnd=slv.find(dfn[u]);
        assert(fnd!=slv.end());
        auto l=fnd,r=fnd;
        if(fnd==(--slv.end())){
            ans-=getans(*(--l),*fnd);
            slv.erase(fnd);
            return;
        }
        --l;++r;
        ans-=getans(*l,*fnd);
        ans-=getans(*fnd,*r);
        ans+=getans(*l,*r);
        slv.erase(fnd);
    }
    auto get(){return ans;}
    void registers(int n){
        G.resize(n+1);inid.resize(n+1);
        dis.resize(n+1);w.resize(n+1);
        h.resize(n+1);dfn.resize(n+1);
        rdfn.resize(n+1);
    }
    solver():ans(0){}
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int n;fcin>>n;solver slv;
    slv.registers(n);
    cir(i,1,n+1) fcin>>w[i];
    cir(i,0,n-1){
        int u,v;fcin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    [&](){
        int dc=0;dfs(1,dc);
        sq.registers(nq);
    }();
    int m;fcin>>m;set<int> insc{1};
    cir(i,0,m){
        int u;fcin>>u;insc.insert(dfn[u]);
    }
    for(auto&i:insc) slv.insert(rdfn[i]);
    fcout<<slv.get()+w[1]<<'\n';
    int q;fcin>>q;
    while(q--){
        int op,x;fcin>>op>>x;
        if(x!=1) if(op==1){
            slv.insert(x);
        }else{
            slv.extract(x);
        }
        fcout<<slv.get()+w[1]<<'\n';
    }
    return 0;
}
