#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e12l);
class segment{
private:
    struct node{
        lint mx,sum;
        friend auto operator+(node a,node b){
            return node(max(a.mx,b.mx),a.sum+b.sum);
        }
        node(lint _mx=-_infl,lint _s=0):mx(_mx),sum(_s){}
    };
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto maintain(int u){
        tr[u]=tr[ls(u)]+tr[rs(u)];
    }
    auto update(int u,int l,int r,int p,lint val){
        if(l==r) return tr[u].mx=tr[u].sum=val,void();
        const auto mid=(l+r)/2;
        p-1<mid?update(ls(u),l,mid,p,val):update(rs(u),mid+1,r,p,val);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(qr<l||r<ql) return node();
        if(ql-1<l&&r-1<qr) return tr[u];
        const auto mid=(l+r)/2;
        return query(ls(u),l,mid,ql,qr)+query(rs(u),mid+1,r,ql,qr);
    }
    const int n;
public:
    auto update(int p,lint w){
        update(1,0,n-1,p,w);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    static auto nullnode(){return node();}
    segment(int _n):tr(_n<<2),n(_n){}
};
class tree{
private:
    vector<vector<int>> gr;
    vector<int> vis,top,bottom,dfn,siz,fr,rdfn;
    segment sg;
    auto init(int u,int f=-1)->int{
        fr[u]=f;
        if(f>-1) gr[u].erase(find(gr[u].begin(),gr[u].end(),f));
        siz[u]=1;
        for(auto&i:gr[u]) siz[u]+=init(i,u);
        sort(gr[u].begin(),gr[u].end(),[&](auto a,auto b){
            return siz[a]>siz[b];
        });
        return siz[u];
    }
    auto dfs(int u,int utop,auto&dcnt){
        top[u]=utop;
        bottom[utop]=u;
        rdfn[dfn[u]=++dcnt]=u;
        if(gr[u].empty()) return;
        dfs(gr[u][0],utop,dcnt);
        for(auto&i:gr[u]) if(i!=gr[u][0]) dfs(i,i,dcnt);
    }
    auto lca(int u,int v){
        auto ux=u,vx=v;
        while(vx>-1) vis[top[vx]]=dfn[vx],vx=fr[top[vx]];
        while(!(~vis[top[ux]])) ux=fr[top[ux]];
        vx=v;
        const auto vux=vis[top[ux]];
        while(vx>-1) vis[top[vx]]=-1,vx=fr[top[vx]];
        return rdfn[min(dfn[ux],vux)];
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto init(){
        init(0);
        auto c=-1;dfs(0,0,c);
    }
    auto update(int p,lint w){
        sg.update(dfn[p],w);
    }
    auto query(int u,int v){
        const auto l=lca(u,v);
        auto res=segment::nullnode();
        while(top[u]!=top[l]){
            res=res+sg.query(dfn[top[u]],dfn[u]);
            u=fr[top[u]];
        }
        while(top[v]!=top[l]){
            res=res+sg.query(dfn[top[v]],dfn[v]);
            v=fr[top[v]];
        }
        res=res+sg.query(dfn[l],dfn[u]);
        if(dfn[v]!=dfn[l]) res=res+sg.query(dfn[l]+1,dfn[v]);
        return res;
    }
    tree(int _n):gr(_n),vis(_n,-1),top(_n),bottom(_n),dfn(_n),rdfn(_n),siz(_n),fr(_n),sg(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree gr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u,v);
    }
    gr.init();
    cir(i,0,n){
        lint w;cin>>w;
        gr.update(i,w);
    }
    int q;cin>>q;
    cir(i,0,q){
        string op;cin>>op;
        if(op=="CHANGE"){
            int p;lint w;cin>>p>>w;--p;
            gr.update(p,w);
        }else if(op=="QMAX"){
            int u,v;cin>>u>>v;--u;--v;
            cout<<gr.query(u,v).mx<<'\n';
        }else{
            int u,v;cin>>u>>v;--u;--v;
            cout<<gr.query(u,v).sum<<'\n';
        }
    }
    return 0;
}

