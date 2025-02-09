#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class random_engine{
private:
    mt19937 eng;
public:
    template<typename _Ty>
    auto randint(auto l,auto r){
        return eng()%r;//uniform_int_distribution<_Ty>(l,r)(eng);
    }
    random_engine():eng(random_device().operator()()){}
} rnd;
class treap{
private:
    struct node{
        int ls,rs,f,key,kt,siz;
        node():ls(0),rs(0),f(0),key(0),kt(0),siz(1){}
    };
    vector<node> s;
    int cur,root;
    auto push_down(int u){
        for(auto v:{s[u].ls,s[u].rs}) v?s[v].key+=s[u].kt,s[v].kt+=s[u].kt:0;
        s[u].kt=0;
    }
    auto down(int u)->void{
        if(s[u].f) down(s[u].f);
        push_down(u);
    }
    auto maintain(int u)->void{
        s[u].siz=(s[u].ls?s[s[u].ls].siz:0)+(s[u].rs?s[s[u].rs].siz:0)+1;
    }
    auto split(int u,int w){
        if(!u) return pair(0,0);
        push_down(u);
        if(s[u].key>w){
            if(s[u].ls) s[s[u].ls].f=0;
            const auto[ux,vx]=split(s[u].ls,w);
            s[u].ls=vx;
            if(vx) s[s[u].ls].f=u;
            maintain(u);
            return pair(ux,u);
        }else{
            if(s[u].rs) s[s[u].rs].f=0;
            const auto[ux,vx]=split(s[u].rs,w);
            s[u].rs=ux;
            if(ux) s[s[u].rs].f=u;
            maintain(u);
            return pair(u,vx);
        }
    }
    auto merge(int u,int v){
        if((!u)||(!v)) return u|v;
        if(rnd.randint<int>(0,s[u].siz+s[v].siz)<s[u].siz){
            push_down(u);
            s[u].rs=merge(s[u].rs,v);
            s[s[u].rs].f=u;
            maintain(u);
            return u;
        }else{
            push_down(v);
            s[v].ls=merge(u,s[v].ls);
            s[s[v].ls].f=v;
            maintain(v);
            return v;
        }
    }
public:
    using iterator=int;
    auto new_node(){
        auto res=++cur;
        root=merge(res,root);
        return res;
    }
    auto shift(int l,int r){
        const auto[ul,ux]=split(root,l-1);
        const auto[um,ur]=split(ux,r);
        if(um) ++s[um].key,++s[um].kt;
        root=merge(merge(ul,um),ur);
    }
    auto access(int u){return down(u),&s[u];}
    treap(auto _n):root(0),s(_n+1),cur(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;vector<int> l(n),r(n);
    cir(i,0,n) cin>>l[i]>>r[i];
    vector<vector<int>> sl(n),sr(n);
    vector<treap::iterator> pos(q);
    cir(i,0,q){
        int l,r;cin>>l>>r;--l;--r;
        sl[l].emplace_back(i);
        sr[r].emplace_back(i);
    }
    treap cur(q);
    vector<int> ans(q);
    cir(i,0,n){
        for(auto&u:sl[i]) pos[u]=cur.new_node();
        cur.shift(l[i],r[i]);
        for(auto&u:sr[i]) ans[u]=cur.access(pos[u])->key;
    }
    ranges::copy(ans,ostream_iterator<int>(cout,"\n"));
    return 0;
}
