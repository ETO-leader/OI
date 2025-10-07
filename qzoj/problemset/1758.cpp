#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
class segment{
private:
    struct node{
        lint sum,add;
        int siz;
        auto addtag(lint x){
            sum+=x*siz;add+=x;
        }
        node():sum(0),add(0),siz(0){}
    };
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto push_down(int u){
        tr[ls(u)].addtag(tr[u].add);
        tr[rs(u)].addtag(tr[u].add);
        tr[u].add=0;
    }
    auto maintain(int u){
        tr[u].sum=tr[ls(u)].sum+tr[rs(u)].sum;
    }
    auto build(int u,int l,int r){
        tr[u].siz=r-l+1;
        if(l==r) return;
        const auto mid=(l+r)/2;
        build(ls(u),l,mid);
        build(rs(u),mid+1,r);
    }
    auto update(int u,int l,int r,int ql,int qr,lint w){
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr) return tr[u].addtag(w);
        const auto mid=(l+r)/2;
        push_down(u);
        update(ls(u),l,mid,ql,qr,w);
        update(rs(u),mid+1,r,ql,qr,w);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(qr<l||r<ql) return 0ll;
        if(ql-1<l&&r-1<qr) return tr[u].sum;
        const auto mid=(l+r)/2;
        push_down(u);
        return query(ls(u),l,mid,ql,qr)+query(rs(u),mid+1,r,ql,qr);
    }
    const int n;
public:
    auto update(int l,int r,lint w){
        update(1,0,n-1,l,r,w);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n):tr(_n<<2),n(_n){build(1,0,_n-1);}
};
class tree{
private:
    vector<vector<int>> gr;
    vector<int> vis,top,bottom,dfn,rdfn,siz,fr;
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
        rdfn[u]=dfn[u]=++dcnt;
        if(gr[u].empty()) return;
        dfs(gr[u][0],utop,dcnt);
        for(auto&i:gr[u]) if(i!=gr[u][0]) dfs(i,i,dcnt);
        rdfn[u]=dcnt;
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
    auto update_node(int u,auto w){
        sg.update(dfn[u],dfn[u],w);
    }
    auto update_sub(int u,auto w){
        sg.update(dfn[u],rdfn[u],w);
    }
    auto query(int u){
        auto res=0ll;
        for(;~u;u=fr[top[u]]) res+=sg.query(dfn[top[u]],dfn[u]);
        return res;
    }
    tree(int _n):gr(_n),vis(_n,-1),top(_n),bottom(_n),dfn(_n),rdfn(_n),siz(_n),fr(_n),sg(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;tree gr(n);
    vector<lint> sw(n);
    for(auto&i:sw) cin>>i;
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u,v);
    }
    gr.init();
    cir(i,0,n) gr.update_node(i,sw[i]);
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int u,w;cin>>u>>w;--u;
            gr.update_node(u,w);
        }else if(op==2){
            int u,w;cin>>u>>w;--u;
            gr.update_sub(u,w);
        }else{
            int u;cin>>u;--u;
            cout<<gr.query(u)<<'\n';
        }
    }
    return 0;
}
