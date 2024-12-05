#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxv=(lint)(1e10l);
class line{
private:
    lint k,b;
public:
    constexpr auto f(auto x) const{return k*x+b;}
    line(auto _k,auto _b):k(_k),b(_b){}
    line()=default;
};
struct node{
    node*ls,*rs;
    line cur;
    node()=default;
    node(auto ln):ls(nullptr),rs(nullptr),cur(ln){}
    // ~node(){for(auto v:{ls,rs}) if(v) delete v;}
};
node*pool;
class segment{
private:
    node*root;
    auto newnode(line ln){
        auto res=++pool;res->cur=ln;
        res->ls=nullptr;res->rs=nullptr;
        return res;
    }
    auto insert(node*&u,lint l,lint r,line ln){
        if(!u) return u=newnode(ln),void();
        if(u->cur.f(l)>ln.f(l)-1&&u->cur.f(r)>ln.f(r)-1) return;
        if(u->cur.f(l)<ln.f(l)+1&&u->cur.f(r)<ln.f(r)+1) return u->cur=ln,void();
        const auto mid=(l+r)/2;
        const auto nl=u->cur;
        if(ln.f(mid)>nl.f(mid)){
            u->cur=ln;
            if(nl.f(l)>ln.f(l)) insert(u->ls,l,mid,nl);
            else insert(u->rs,mid+1,r,nl);
        }else{
            if(nl.f(l)<ln.f(l)) insert(u->ls,l,mid,ln);
            else insert(u->rs,mid+1,r,ln);
        }
    }
    auto query(node*u,lint l,lint r,lint p){
        if(!u) return 0ll;
        const auto mid=(l+r)/2;
        return max(u->cur.f(p),p-1<mid?query(u->ls,l,mid,p):query(u->rs,mid+1,r,p));
    }
    lint n;
public:
    auto insert(line l){
        return insert(root,0,n-1,l);
    }
    auto query(lint x){
        return query(root,0,n-1,x);
    }
    auto clear(){
        // if(root) delete root;
        root=nullptr;
    }
    segment(auto _v):n(_v),root(nullptr){}
    // ~segment(){if(root) delete root;}
};
class blocks{
private:
    vector<segment> lc,rlc;
    vector<lint> delta,a,b;
    int sqr;
    constexpr auto block(auto u){return u/sqr;}
    constexpr auto lpos(auto b){return b*sqr;}
    constexpr auto rpos(auto b){return min(lpos(b+1),(int)(a.size()))-1;}
    auto rebuild(int bl){
        const auto l=lpos(bl),r=rpos(bl);
        cir(i,l,r+1) a[i]+=delta[bl];
        lc[bl].clear();rlc[bl].clear();
        cir(i,l,r+1) lc[bl].insert(line(b[i],a[i]*b[i]));
        cir(i,l,r+1) rlc[bl].insert(line(-b[i],(-a[i])*b[i]));
        delta[bl]=0;
    }
public:
    auto update(int l,int r,lint x){
        const auto lb=block(l),rb=block(r);
        if(lb==rb){
            cir(i,l,r+1) a[i]+=x;
            return rebuild(lb);
        }
        cir(i,l,rpos(lb)+1) a[i]+=x;
        cir(i,lpos(rb),r+1) a[i]+=x;
        rebuild(lb);rebuild(rb);
        cir(i,lb+1,rb) delta[i]+=x;
    }
    auto query(int l,int r){
        const auto lb=block(l),rb=block(r);
        auto res=0ll;
        if(lb==rb){
            cir(i,l,r+1) res=max(res,abs(a[i]+delta[lb])*b[i]);
            return res;
        }
        cir(i,l,rpos(lb)+1) res=max(res,abs(a[i]+delta[lb])*b[i]);
        cir(i,lpos(rb),r+1) res=max(res,abs(a[i]+delta[rb])*b[i]);
        cir(i,lb+1,rb) res=max({res,lc[i].query(delta[i]),rlc[i].query(delta[i])});
        return res;
    }
    auto build(vector<lint> _a,vector<lint> _b){
        a=_a;b=_b;
        cir(i,0,(int)(a.size())/sqr+3) rebuild(i);
    }
    blocks(int _n):sqr(sqrt(_n/log2(_n+1))+1),lc(_n+7,segment(maxv)),rlc(_n+7,segment(maxv)),delta(_n+7),a(_n),b(_n){}
};
class tree{
private:
    vector<vector<int>> gr;
    vector<int> dfn,las;
    auto dfs(int u,int&cnt,int f=-1)->void{
        dfn[u]=++cnt;
        for(auto&i:gr[u]) if(i!=f) dfs(i,cnt,u);
        las[u]=cnt;
    }
public:
    auto link(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto init(){
        auto cnt=-1;dfs(0,cnt);
        return pair(dfn,las);
    }
    tree(int _n):gr(_n),dfn(_n),las(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;tree gr(n);
    pool=new node[5000000];
    cir(i,1,n){
        int f;cin>>f;--f;
        gr.link(i,f);
    }
    const auto[dfn,las]=gr.init();
    vector<lint> pa(n),pb(n);
    cir(i,0,n){
        lint w;cin>>w;pa[dfn[i]]+=w;
        if(las[i]<n-1) pa[las[i]+1]-=w;
    }
    cir(i,0,n){
        lint w;cin>>w;pb[dfn[i]]+=w;
        if(las[i]<n-1) pb[las[i]+1]-=w;
    }
    cir(i,1,n) pa[i]+=pa[i-1];
    cir(i,1,n) pb[i]+=pb[i-1];
    for(auto&i:pb) i=abs(i);
    blocks bx(n);
    bx.build(pa,pb);
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int u;lint x;cin>>u>>x;--u;
            bx.update(dfn[u],las[u],x);
        }else{
            int u;cin>>u;--u;
            cout<<bx.query(dfn[u],las[u])<<'\n';
        }
    }
    return 0;
}
