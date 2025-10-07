#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e12l);
class segment{
private:
    struct node{
        int sum,fll,siz;
        auto fill(int x){
            sum=x*siz;fll=x;
        }
        node():sum(0),fll(-1),siz(0){}
    };
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto push_down(int u){
        if(tr[u].fll<0) return;
        tr[ls(u)].fill(tr[u].fll);
        tr[rs(u)].fill(tr[u].fll);
        tr[u].fll=-1;
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
    auto update(int u,int l,int r,int ql,int qr,int w){
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr) return tr[u].fill(w);
        const auto mid=(l+r)/2;
        push_down(u);
        update(ls(u),l,mid,ql,qr,w);
        update(rs(u),mid+1,r,ql,qr,w);
        maintain(u);
    }
    const int n;
public:
    auto update(int l,int r,int w){
        update(1,0,n-1,l,r,w);
    }
    auto query(){
        return tr[1].sum;
    }
    segment(int _n):tr(_n<<2),n(_n){build(1,0,_n-1);}
};
class tree{
private:
    vector<vector<int>> gr;
    vector<int> top,dfn,rdfn,siz,fr;
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
        dfn[u]=rdfn[u]=++dcnt;
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
    auto install(int u){
        while(~u){
            sg.update(dfn[top[u]],dfn[u],1);
            u=fr[top[u]];
        }
    }
    auto remove(int u){
        sg.update(dfn[u],rdfn[u],0);
    }
    auto query(){return sg.query();}
    tree(int _n):gr(_n),top(_n),dfn(_n),rdfn(_n),siz(_n),fr(_n),sg(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree gr(n);
    cir(i,1,n){
        int u;cin>>u;
        gr.link(u,i);
    }
    gr.init();
    auto cnt=0;
    int q;cin>>q;
    cir(i,0,q){
        string op;cin>>op;
        if(op=="install"){
            int u;cin>>u;
            gr.install(u);
            cout<<abs(gr.query()-cnt)<<'\n';
            cnt=gr.query();
        }else{
            int u;cin>>u;
            gr.remove(u);
            cout<<abs(gr.query()-cnt)<<'\n';
            cnt=gr.query();
        }
    }
    return 0;
}
