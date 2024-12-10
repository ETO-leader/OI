#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class casereader{
private:
    union datatype{
        int i32;
        char chr;
        datatype(int x):i32(x){}
        datatype(char c):chr(c){}
    };
    vector<datatype> ax;
    int cur;
    template<typename _Ty>
    auto readarg(){
        _Ty x;cin>>x;ax.emplace_back(x);
        return x;
    }
public:
    auto init(){
        const auto n=readarg<int>(),m=readarg<int>();
        cir(i,0,m){
            readarg<char>();
            readarg<int>();readarg<int>();
        }
        cur=0;
    }
    auto iterator(){return cur;}
    auto fseek(int x){cur=x;}
    auto readargs(int&x){
        x=ax[cur].i32;++cur;
    }
    auto readargs(char&x){
        x=ax[cur].chr;++cur;
    }
    auto readargs(auto&x,auto&...args){
        readargs(x);readargs(args...);
    }
};
class random_engine{
private:
    mt19937_64 eng;
public:
    template<typename _Ty>
    auto randint(auto l,auto r){
        return uniform_int_distribution<int>(l,r)(eng);
    }
    random_engine():eng(
        #ifdef local
            251
        #else
            random_device().operator()()
        #endif
    ){}
} rnd;
class ett{
private:
    struct node{
        int ls,rs,fa,val,siz;
        node():ls(0),rs(0),fa(0),val(0),siz(1){}
    };
    vector<node> tr;
    constexpr auto&ls(auto u){return tr[u].ls;}
    constexpr auto&rs(auto u){return tr[u].rs;}
    constexpr auto&fa(auto u){return tr[u].fa;}
    auto maintain(int u){
        tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+1;
    }
    auto getroot(int u){
        while(fa(u)) u=fa(u);
        return u;
    }
    auto getrank(int u){
        auto res=tr[ls(u)].siz+1;
        while(fa(u)){
            if(ls(fa(u))!=u) res+=tr[ls(fa(u))].siz+1;
            u=fa(u);
        }
        return res;
    }
    auto split(int u,int rk){
        if(!u) return pair(0,0);
        if(tr[ls(u)].siz>rk-1){
            fa(ls(u))=0;
            const auto[ux,vx]=split(ls(u),rk);
            ls(u)=vx;maintain(u);
            fa(ls(u))=u;
            return pair(ux,u);
        }else{
            fa(rs(u))=0;
            const auto[ux,vx]=split(rs(u),rk-tr[ls(u)].siz-1);
            rs(u)=ux;maintain(u);
            fa(rs(u))=u;
            return pair(u,vx);
        }
    }
    auto merge(int u,int v){
        if((!u)||(!v)) return u|v;
        if(rnd.randint<int>(0,tr[u].siz+tr[v].siz)<tr[u].siz){
            rs(u)=merge(rs(u),v);
            fa(rs(u))=u;
            maintain(u);
            return u;
        }else{
            ls(v)=merge(u,ls(v));
            fa(ls(v))=v;
            maintain(v);
            return v;
        }
    }
    int n;
public:
    auto linkfa(int u,int v){
        ++u;++v;
        const auto[lf,qrg]=split(getroot(u),getrank(u)-1);
        const auto[sub,rg]=split(getroot(u+n),getrank(u+n));
        merge(lf,rg);
        const auto[xl,xr]=split(getroot(v+n),getrank(v+n)-1);
        merge(merge(xl,sub),xr);
    }
    auto query(int u,int v){
        ++u;++v;
        const auto siz=tr[getroot(v)].siz/2;
        const auto subsiz=(getrank(u+n)-getrank(u)+1)/2;
        return (lint)(siz-subsiz)*subsiz;
    }
    ett(int _n):n(_n+3),tr(_n*2+7){
        tr[0].siz=0;
        cir(i,1,_n+3) merge(i,i+_n+3);
    }
};
class forest{
private:
    vector<vector<int>> gr;
    vector<int> fx;
    auto dfs(int u,int f=-1)->void{
        fx[u]=f;
        for(auto&i:gr[u]) if(i!=f) dfs(i,u);
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto check(){
        cir(i,0,(int)(gr.size())) if(fx[i]==-1) dfs(i);
    }
    auto fr(auto u) const{return fx[u];}
    forest(int _n):gr(_n),fx(_n,-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;inf.init();
    int n,m;inf.readargs(n,m);
    forest fr(n);
    const auto sk=inf.iterator();
    cir(i,0,m){
        char op;int u,v;inf.readargs(op,u,v);
        --u;--v;
        if(op=='A') fr.link(u,v);
    }
    fr.check();
    inf.fseek(sk);
    ett ex(n);
    cir(i,0,m){
        char op;int u,v;inf.readargs(op,u,v);
        --u;--v;
        if(fr.fr(u)!=v) swap(u,v);
        if(op=='A') ex.linkfa(u,v);
        else cout<<ex.query(u,v)<<'\n';
    }
    return 0;
}
