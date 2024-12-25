#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class casereader{};
class link_cut_tree{
private:
    struct node{
        int val,sum,f;
        array<int,2> ch;
        bool rev;
        node(int _v=0):val(_v),sum(_v),f(0),ch({0,0}),rev(false){}
    };
    vector<node> tr;
    auto&ls(auto u){return tr[u].ch[0];}
    auto&rs(auto u){return tr[u].ch[1];}
    auto&f(auto u){return tr[u].f;}
    auto nrt(auto u){return ls(f(u))==u||rs(f(u))==u;}
    auto dir(auto u){return rs(f(u))==u;}
    auto rev(auto u){
        swap(ls(u),rs(u));
        tr[u].rev^=true;
    }
    auto push_down(int u){
        if(tr[u].rev) for(auto v:tr[u].ch) if(v) rev(v);
        tr[u].rev=false;
    }
    auto maintain(int u){
        tr[u].sum=tr[ls(u)].sum+tr[rs(u)].sum+tr[u].val;
    }
    auto rotate(int u){
        const auto fu=f(u),gu=f(fu),c=(int)(dir(u));
        if(nrt(fu)) tr[gu].ch[dir(fu)]=u;
        f(u)=gu;
        tr[fu].ch[c]=tr[u].ch[c^1];f(tr[u].ch[c^1])=fu;
        tr[u].ch[c^1]=fu;f(fu)=u;
        maintain(fu);maintain(u);
    }
    auto down(int u)->void{
        if(nrt(u)) down(f(u));
        push_down(u);
    }
    auto splay(int u){
        for(down(u);nrt(u);rotate(u)){
            if(nrt(f(u))) rotate(dir(f(u))==dir(u)?f(u):u);
        }
    }
    auto access(int u){
        for(int v=0;u;v=u,u=f(u)){
            splay(u);rs(u)=v;maintain(u);
        }
    }
    auto makeroot(int u){
        access(u);splay(u);rev(u);
    }
    auto split(int u,int v){
        makeroot(u);access(v);splay(u);
    }
public:
    auto link(int u,int v){
        ++u;++v;
        makeroot(u);f(u)=v;
    }
    auto initval(int u,int w){
        ++u;
        split(u,u);tr[u]=node(w);
    }
    auto query(int u,int v){
        ++u;++v;
        split(u,v);
        return tr[u].sum;
    }
    link_cut_tree(int n):tr(n+1){}
};
template<const int alpha>
class ext_suffixam{
private:
    vector<array<int,alpha>> ch;
    vector<int> len,fail;
public:
}
