#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
class node:public array<array<lint,2>,2>{
public:
    auto operator+(node x) const{
        auto res=node();
        cir(kl,0,2) cir(kr,0,2) if(!(kl&&kr)) cir(i,0,2) cir(j,0,2){
            res[i][j]=max(res[i][j],(*this)[i][kl]+x[kr][j]);
        }
        return res;
    }
    node(){for(auto&x:(*this)) for(auto&i:x) i=-_infl;}
};
class segment{
private:
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto maintain(int u){
        tr[u]=tr[ls(u)]+tr[rs(u)];
    }
    auto update(int u,int l,int r,int p,node w){
        if(l==r) return tr[u]=w,void();
        const auto mid=(l+r)/2;
        p-1<mid?update(ls(u),l,mid,p,w):update(rs(u),mid+1,r,p,w);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(ql-1<l&&r-1<qr) return tr[u];
        const auto mid=(l+r)/2;
        if(qr<mid+1) return query(ls(u),l,mid,ql,qr);
        if(mid<ql) return query(rs(u),mid+1,r,ql,qr);
        return query(ls(u),l,mid,ql,qr)+query(rs(u),mid+1,r,ql,qr); 
    }
    const int n;
public:
    auto update(int p,node w){
        update(1,0,n-1,p,w);
    }
    auto query(int l,int r){
        const auto x=query(1,0,n-1,l,r);
        return array<lint,2>{max(x[0][0],x[0][1]),max({x[0][0],x[0][1],x[1][0],x[1][1]})};
    }
    segment(int _n):tr(_n<<2),n(_n){}
};
class tree{
private:
    vector<vector<int>> gr;
    vector<array<lint,2>> info,updinfo;
    vector<int> top,dfn,anc,siz,bottom;
    segment sg;
    vector<lint> val;
    auto init(int u,int f=-1)->int{
        anc[u]=f;siz[u]=1;
        if(f>-1) gr[u].erase(find(gr[u].begin(),gr[u].end(),f));
        for(auto&i:gr[u]) if(i!=f) siz[u]+=init(i,u);
        return siz[u];
    }
    auto dfs(int u,int&cnt,int utop=-1){
        if(utop<0) utop=u;
        top[u]=utop;
        bottom[utop]=u;
        dfn[u]=++cnt;
        sort(gr[u].begin(),gr[u].end(),[&](auto u,auto v){
            return siz[u]>siz[v];
        });
        if(gr[u].empty()) return;
        dfs(gr[u][0],cnt,utop);
        for(auto&i:gr[u]) if(i!=gr[u][0]) dfs(i,cnt);
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto init(vector<lint> w){
        init(0);
        auto c=-1;
        dfs(0,c);
        val=w;
        vector<int> ord(gr.size());
        iota(ord.begin(),ord.end(),0);
        sort(ord.begin(),ord.end(),[&](auto x,auto y){return dfn[x]>dfn[y];});
        for(auto&u:ord){
            auto upd=node();
            upd[0][0]=info[u][1];
            upd[1][1]=info[u][0]+val[u];
            sg.update(dfn[u],upd);
            if(u==top[u]){
                updinfo[u]=sg.query(dfn[u],dfn[bottom[u]]);
                if(anc[u]>-1){
                    info[anc[u]][0]+=updinfo[u][0];
                    info[anc[u]][1]+=updinfo[u][1];
                }
            }
        }
    }
    auto update(int u,lint w){
        val[u]=w;
        while(u>-1){
            auto upd=node();
            upd[0][0]=info[u][1];
            upd[1][1]=info[u][0]+val[u];
            sg.update(dfn[u],upd);
            u=top[u];
            if(anc[u]>-1){
                info[anc[u]][0]-=updinfo[u][0];
                info[anc[u]][1]-=updinfo[u][1];
            }
            updinfo[u]=sg.query(dfn[u],dfn[bottom[u]]);
            if(anc[u]>-1){
                info[anc[u]][0]+=updinfo[u][0];
                info[anc[u]][1]+=updinfo[u][1];
            }
            u=anc[u];
        }
    }
    auto value(){
        return updinfo[0][1];
    }
    tree(int _n):gr(_n),info(_n),updinfo(_n),top(_n),dfn(_n),siz(_n),anc(_n),bottom(_n),sg(_n),val(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<lint> a(n);
    for(auto&i:a) cin>>i;
    tree gr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u,v);
    }
    gr.init(a);
    int q;cin>>q;
    cir(i,0,q){
        int p;lint w;cin>>p>>w;--p;
        gr.update(p,w);
        cout<<gr.value()<<'\n';
    }
    return 0;
}
