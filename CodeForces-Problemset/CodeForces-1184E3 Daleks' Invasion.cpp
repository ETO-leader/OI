#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9);
template<class comp>
class link_cut_tree{
private:
    static constexpr auto snum=max(_inf,-_inf,comp());
    struct node{
        int wx,tag,mn;
        auto upd(int x){
            for(auto i:{&wx,&tag,&mn}) *i=min(*i,x,comp());
        }
        friend class link_cut_tree;
        node():wx(snum),tag(snum),mn(snum){}
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> rev,f;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){return ls(f[u])==u||rs(f[u])==u;}
    auto getch(int u){return rs(f[u])==u;}
    auto push_down(int u){
        for(auto c:ch[u]) if(c) tr[c].upd(tr[u].tag);
        tr[u].tag=snum;
        if(rev[u]){
            swap(ls(u),rs(u));
            for(auto x:{ls(u),rs(u)}) rev[x]^=true;
            rev[u]=false;
        }
    }
    auto maintain(int u){
        tr[u].mn=min({tr[u].wx,tr[ls(u)].mn,tr[rs(u)].mn},comp());
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu],c=(int)(getch(u));
        if(nrt(fu)) ch[gu][getch(fu)]=u;
        f[u]=gu;
        ch[fu][c]=ch[u][!c];f[ch[u][!c]]=fu;
        ch[u][!c]=fu;f[fu]=u;
        maintain(fu);maintain(u);
    }
    auto down(int u)->void{
        if(nrt(u)) down(f[u]);
        push_down(u);
    }
    auto splay(int u){
        for(down(u);nrt(u);rotate(u));
    }
    auto access(int u){
        for(auto v=0;u;u=f[v=u]){
            splay(u);rs(u)=v;maintain(u);
        }
    }
    auto mkrt(int u){
        access(u);splay(u);
        rev[u]^=true;push_down(u);
    }
    auto split(int u,int v){
        mkrt(u);access(v);splay(v);
    }
public:
    auto link(int u,int v){
        ++u;++v;
        mkrt(u);mkrt(v);
        f[v]=u;
    }
    auto update(int u,int v,int w){
        ++u;++v;
        split(u,v);splay(u);
        tr[u].upd(w);
    }
    auto query(int u,int v){
        ++u;++v;
        split(u,v);splay(u);
        return tr[u].mn;
    }
    link_cut_tree(int _n):tr(_n+1),ch(_n+1),rev(_n+1),f(_n+1){}
};
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){ranges::iota(f,0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    struct edge_t{int u,v,w,id;};
    vector<edge_t> es(m);
    for(auto c=-1;auto&[u,v,w,id]:es) cin>>u>>v>>w,--u,--v,id=++c;
    const auto cpes=es;
    ranges::sort(es,[](auto&a,auto&b){return a.w<b.w;});
    dsu ds(n);
    unordered_set<int> aps;
    link_cut_tree<less<int>> lctl(n+m+7);
    link_cut_tree<greater<int>> lctg(n+m+7);
    for(auto&[u,v,w,id]:es) [&](){
        if(ds.findset(u)==ds.findset(v))
            return lctl.update(u,v,w);
        aps.insert(id);
        lctl.link(u,id+n);
        lctl.link(id+n,v);
        lctg.link(u,id+n);
        lctg.link(id+n,v);
        lctg.update(id+n,id+n,w);
        ds.merge(u,v);
    }();
    for(auto&[u,v,w,id]:cpes){
        if(aps.count(id)) cout<<lctl.query(id+n,id+n)<<'\n';
        else cout<<lctg.query(u,v)<<'\n';
    }
    return 0;
}
