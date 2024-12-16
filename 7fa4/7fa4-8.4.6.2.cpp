#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class casereader{
public:
    auto init(){}
    auto readargs(int&x){cin>>x;}
    auto readargs(string&s){cin>>s;}
    auto readargs(auto&x,auto&...args){
        readargs(x);readargs(args...);
    }
};
class link_cut_tree{
private:
    struct node{
        int siz,spsiz,vsiz;
        int mx;
        multiset<int,greater<int>> vmx;
        node():siz(1),spsiz(1),vsiz(0),mx(0),vmx({0}){}
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> rev,f;
    constexpr auto&ls(auto u){return ch[u][0];}
    constexpr auto&rs(auto u){return ch[u][1];}
    constexpr auto getch(auto u){return rs(f[u])==u;}
    constexpr auto nrt(auto u){return ls(f[u])==u||rs(f[u])==u;}
    auto push_down(int u){
        if(!rev[u]) return;
        swap(ls(u),rs(u));
        rev[ls(u)]^=true;rev[rs(u)]^=true;
        rev[u]=false;
    }
    auto maintain(int u){
        tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+tr[u].vsiz+1;
        tr[u].spsiz=tr[ls(u)].spsiz+tr[rs(u)].spsiz+1;
        tr[u].mx=max({tr[ls(u)].siz,tr[rs(u)].siz,*tr[u].vmx.begin()});
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
        for(down(u);nrt(u);rotate(u)){
            int fu=f[u];
            if(nrt(fu)){
                if(getch(fu)==getch(u)) rotate(fu);
                else rotate(u);
            }
        }
    }
    auto access(int u){
        for(auto v=0;u;u=f[v=u]){
            splay(u);
            if(rs(u)){
                tr[u].vsiz+=tr[rs(u)].siz;
                tr[u].vmx.emplace(tr[rs(u)].siz);
            }
            if(v){
                tr[u].vsiz-=tr[v].siz;
                tr[u].vmx.extract(tr[v].siz);
            }
            rs(u)=v;
            maintain(u);
        }
    }
    auto find_by_order(int u,int rk){
        push_down(u);
        if(tr[ls(u)].spsiz+1==rk) return u;
        return (rk<tr[ls(u)].spsiz+1)?find_by_order(ls(u),rk):find_by_order(rs(u),rk-tr[ls(u)].spsiz-1);
    }
    auto makeroot(int u){
        access(u);splay(u);
        rev[u]^=true;push_down(u);
    }
    auto split(int u,int v){
        makeroot(u);access(v);splay(v);
    }
public:
    auto chksiz(int u){
        ++u;
        makeroot(u);splay(u);
        return tr[u].mx;
    }
    auto link(int u,int v){
        ++u;++v;
        makeroot(u);makeroot(v);
        tr[u].vmx.emplace(tr[v].siz);
        tr[u].vsiz+=tr[v].siz;
        f[v]=u;
        maintain(u);
    }
    auto kthnode(int u,int v,int k){
        ++u;++v;split(u,v);splay(u);
        return find_by_order(u,k+1)-1;
    }
    link_cut_tree(int _n):tr(_n+1),ch(_n+1),rev(_n+1),f(_n+1){
        tr[0].siz=tr[0].spsiz=0;
    }
};
class dsu{
private:
    vector<int> f,siz;
public:
    auto findset(auto u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto getsize(auto u){return siz[findset(u)];}
    auto merge(int u,int v){
        u=findset(u);v=findset(v);
        f[u]=v;siz[v]+=siz[u];
    }
    dsu(int _n):f(_n),siz(_n,1){iota(f.begin(),f.end(),0);}
};
class forest{
private:
    dsu fr;
    vector<int> c;
    link_cut_tree lct;
    int xorsum;
    auto isvaild(int u){
        return lct.chksiz(u)<fr.getsize(u)/2+1;
    }
    auto getnode(int u,int v){
        while(!isvaild(u)) u=lct.kthnode(u,v,1);
        if(u==v) return u;
        const auto nxt=lct.kthnode(u,v,1);
        if(!isvaild(nxt)) return u;
        return min(u,nxt);
    }
public:
    auto link(int u,int v){
        if(fr.getsize(u)<fr.getsize(v)) swap(u,v);
        lct.link(u,v);
        xorsum^=(c[fr.findset(u)]+1);
        xorsum^=(c[fr.findset(v)]+1);
        const auto ux=fr.findset(u),vx=fr.findset(v);
        fr.merge(v,u);
        xorsum^=((c[ux]=getnode(c[ux],c[vx]))+1);
    }
    auto capital(int u){
        return c[fr.findset(u)]+1;
    }
    auto capxor(){return xorsum;}
    forest(int _n):fr(_n),c(_n),lct(_n),xorsum([](int x){
        auto res=0;
        cir(i,1,x+1) res^=i;
        return res;
    }(_n)){iota(c.begin(),c.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;inf.init();
    int n,q;inf.readargs(n,q);
    forest gr(n);
    cir(i,0,q){
        string op;inf.readargs(op);
        if(op=="A"){
            int u,v;inf.readargs(u,v);--u;--v;
            gr.link(u,v);
        }else if(op=="Q"){
            int u;inf.readargs(u);--u;
            cout<<gr.capital(u)<<'\n';
        }else{
            cout<<gr.capxor()<<'\n';
        }
    }
    return 0;
}
