#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
class segment{
private:
    friend class tree;
    struct node{
        int val1,val2;
        int res1,res2;
        int64_t ans1,ans2;
        node():val1(0),val2(1),res1(0),res2(1),ans1(0),ans2(0){}
        node(int v1,int v2,int r1,int r2,int64_t _c1,int64_t _c2):val1(v1),val2(v2),res1(r1),res2(r2),ans1(_c1),ans2(_c2){};
    };
    friend auto operator+(const node a,const node b){
        return node(
            a.val1,
            a.val2,
            a.res1==b.val1?b.res2:b.res1,
            a.res2==b.val1?b.res2:b.res1,
            (a.res1==b.val1?a.ans1+b.ans2:a.ans1+b.ans1)+max(a.res1,0),
            (a.res2==b.val1?a.ans2+b.ans2:a.ans2+b.ans1)+max(a.res2,0)
        );
    }
    vector<node> tr;
    constexpr auto ls(auto x) const{return x*2;}
    constexpr auto rs(auto x) const{return x*2+1;}
    auto maintain(int u){
        tr[u]=tr[rs(u)]+tr[ls(u)];
    }
    auto update(int u,int l,int r,int p,node x){
        if(l==r) return tr[u]=x,void();
        const auto mid=(l+r)/2;
        p-1<mid?update(ls(u),l,mid,p,x):update(rs(u),mid+1,r,p,x);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(ql-1<l&&r-1<qr) return tr[u];
        const auto mid=(l+r)/2;
        if(qr-1<mid) return query(ls(u),l,mid,ql,qr);
        if(mid<ql) return query(rs(u),mid+1,r,ql,qr);
        return query(rs(u),mid+1,r,mid+1,qr)+query(ls(u),l,mid,ql,mid);
    }
    const int n;
public:
    auto update(int p,node x){
        update(1,0,n-1,p,x);
    }
    auto query(int ql,int qr){
        return query(1,0,n-1,ql,qr);
    }
    segment(int _n):n(_n),tr(_n<<2,node(-1,-1,-1,-1,0,0)){}
};
class tree{
private:
    static constexpr auto lgc=31;
    vector<vector<int>> gr;
    vector<int> siz,dfn,rdfn,top,bottom,uf;
    vector<vector<int>> cnt,ok;
    vector<int64_t> tans;
    segment sg;
    auto init(int u,int f=-1)->int{
        siz[u]=1;uf[u]=f;
        if(~f) gr[u].erase(ranges::find(gr[u],f));
        for(auto&i:gr[u]) if(i!=f) siz[u]+=init(i,u);
        ranges::sort(gr[u],ranges::greater{},[&](auto p){
            return siz[p];
        });
        return siz[u];
    }
    auto dfs(int u,auto&c,int utop)->void{
        top[u]=utop;
        dfn[u]=++c;
        bottom[utop]=u;
        if(!gr[u].empty()){
            dfs(gr[u][0],c,utop);
            for(auto&i:gr[u]) if(i!=gr[u][0]) dfs(i,c,i);
        }
        rdfn[u]=c;
    }
    auto flush(int u){
        ok[u].clear();
        cir(i,0,lgc) if(!cnt[u][i]) ok[u].emplace_back(i);
    }
    auto remove(int u){
        u=top[u];
        if(!(~uf[u])) return;
        remove(uf[u]);
        const auto w=sg.query(dfn[u],dfn[bottom[u]]);
        if(~w.res1) --cnt[uf[u]][w.res1];
        flush(uf[u]);
        tans[uf[u]]-=w.ans1+max(w.res1,0);
        auto upd=segment::node(ok[uf[u]][0],ok[uf[u]][1],ok[uf[u]][0],ok[uf[u]][1],tans[uf[u]],tans[uf[u]]);
        sg.update(dfn[uf[u]],upd);
    }
    auto emplace(int u){
        u=top[u];
        if(!(~uf[u])) return;
        const auto w=sg.query(dfn[u],dfn[bottom[u]]);
        if(~w.res1) ++cnt[uf[u]][w.res1];
        flush(uf[u]);
        tans[uf[u]]+=w.ans1+max(w.res1,0);
        auto upd=segment::node(ok[uf[u]][0],ok[uf[u]][1],ok[uf[u]][0],ok[uf[u]][1],tans[uf[u]],tans[uf[u]]);
        // clog<<u<<": "<<uf[u]<<' '<<ok[uf[u]][0]<<' '<<ok[uf[u]][1]<<'\n';
        sg.update(dfn[uf[u]],upd);
        emplace(uf[u]);
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto init(){
        init(0);
        auto c=-1;
        dfs(0,c,0);
    }
    auto active(int u){
        if(~uf[u]) remove(uf[u]);
        sg.update(dfn[u],segment::node());
        emplace(u);
    }
    auto query(){
        // clog<<
        //     sg.query(dfn[0],dfn[bottom[0]]).val1<<' '<<
        //     sg.query(dfn[0],dfn[bottom[0]]).val2<<' '<<
        //     sg.query(dfn[0],dfn[bottom[0]]).res1<<' '<<
        //     sg.query(dfn[0],dfn[bottom[0]]).res2<<'\n';
        const auto res=sg.query(dfn[0],dfn[bottom[0]]);
        return res.ans1+res.res1;
    }
    tree(int _n):
        gr(_n),
        siz(_n),dfn(_n),rdfn(_n),top(_n),bottom(_n),uf(_n),tans(_n),
        cnt(_n,vector<int>(lgc)),ok(_n),
        sg(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;++n;tree gr(n);
    cir(i,1,n){
        int f;cin>>f;--f;
        gr.link(f,i);
    }
    gr.init();
    gr.active(0);
    // clog<<gr.query()<<'\n';
    cir(i,1,n){
        gr.active(i);
        cout<<gr.query()<<'\n';
    }
    return 0;
}
