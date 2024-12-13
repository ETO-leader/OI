#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class casereader{
private:
    union datatype{
        int i32;
        datatype(int x):i32(x){}
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
        const auto n=readarg<int>();
        cir(i,0,(n-1)*2) readarg<int>();
        const auto q=readarg<int>();
        cir(i,0,q*2) readarg<int>();
    }
    auto readargs(int&x){
        x=ax[cur].i32;++cur;
    }
    auto readargs(auto&x,auto&...args){
        readargs(x);readargs(args...);
    }
    casereader():cur(0){}
};
class random_engine{
private:
    mt19937_64 eng;
public:
    template<typename _Ty>
    auto randint(auto l,auto r){
        return uniform_int_distribution<_Ty>(l,r)(eng);
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
        int ls,rs,fr,siz;
        node():ls(0),rs(0),fr(0),siz(1){}
    };
    vector<node> tr;
    constexpr auto&ls(auto u){return tr[u].ls;}
    constexpr auto&rs(auto u){return tr[u].rs;}
    constexpr auto&fr(auto u){return tr[u].fr;}
    constexpr auto getch(auto u){return rs(fr(u))==u;}
    auto maintain(int u){
        tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+1;
    }
    auto getroot(int u){
        while(fr(u)) u=fr(u);
        return u;
    }
    auto getfirst(int u){
        while(ls(u)) u=ls(u);
        return u;
    }
    auto getrank(int u){
        auto res=tr[ls(u)].siz+1;
        while(fr(u)){
            if(getch(u)) res+=tr[ls(fr(u))].siz+1;
            u=fr(u);
        }
        return res;
    }
    auto split(int u,int rk){
        if(!u) return pair(0,0);
        if(tr[ls(u)].siz>rk-1){
            const auto[ux,vx]=split(ls(u),rk);
            fr(ux)=0;ls(u)=vx;
            if(vx) fr(vx)=u;
            maintain(u);
            return pair(ux,u);
        }else{
            const auto[ux,vx]=split(rs(u),rk-tr[ls(u)].siz-1);
            fr(vx)=0;rs(u)=ux;
            if(ux) fr(ux)=u;
            maintain(u);
            return pair(u,vx);
        }
    }
    auto merge(int u,int v){
        if((!u)||(!v)) return u|v;
        if(rnd.randint<int>(0,tr[u].siz+tr[v].siz-1)<tr[u].siz){
            fr(rs(u))=0;
            rs(u)=merge(rs(u),v);
            if(rs(u)) fr(rs(u))=u;
            return maintain(u),u;
        }else{
            fr(ls(v))=0;
            ls(v)=merge(u,ls(v));
            if(ls(v)) fr(ls(v))=v;
            return maintain(v),v;
        }
    }
    int n;
public:
    auto linkfa(int u,int v){
        ++u;++v;
        const auto[lf,qrg]=split(getroot(u),getrank(u)-1);
        const auto[sub,rg]=split(getroot(u+n),getrank(u+n));
        merge(lf,rg);
        const auto[al,ar]=split(getroot(v+n),getrank(v+n)-1);
        merge(merge(al,sub),ar);
    }
    auto cut(int u){
        ++u;
        const auto[lf,qrg]=split(getroot(u),getrank(u)-1);
        const auto[sub,rg]=split(getroot(u+n),getrank(u+n));
        merge(lf,rg);
    }
    auto subsize(int u){
        ++u;
        return (getrank(u+n)-getrank(u)+1)/2;
    }
    auto getanc(int u){
        ++u;
        return getfirst(getroot(u))-1;
    }
    ett(int _n):n(_n+3),tr(_n*2+7){
        tr[0].siz=0;
        cir(i,1,_n+1) merge(i,i+_n+3);
    }
};
class tree{
private:
    vector<vector<int>> gr,up;
    vector<int> fr,dfn,rdfn;
    static constexpr auto ups=21;
    auto dfs(int u,int&cdfn,int f=0)->void{
        up[u][0]=fr[u]=f;dfn[u]=++cdfn;
        cir(i,1,ups) up[u][i]=up[up[u][i-1]][i-1];
        for(auto&i:gr[u]) if(i!=f) dfs(i,cdfn,u);
        rdfn[u]=cdfn;
    }
    auto isancestor(int u,int v){
        return dfn[u]-1<dfn[v]&&rdfn[v]-1<rdfn[u];
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto init(){
        auto cdfn=-1;dfs(0,cdfn);
    }
    auto father(int u) const{return fr[u];}
    auto getchild(int u,int v){
        for(auto i=ups-1;~i;--i) if(up[u][i]!=v&&isancestor(v,up[u][i])) u=up[u][i];
        return u;
    }
    tree(int _n):gr(_n),up(_n,vector<int>(ups)),fr(_n),dfn(_n),rdfn(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;inf.init();
    int n;inf.readargs(n);++n;
    tree gr(n);
    gr.link(0,1);
    cir(i,0,n-2){
        int u,v;inf.readargs(u,v);
        gr.link(u,v);
    }
    gr.init();
    ett wh(n),bl(n);
    cir(i,1,n) wh.linkfa(i,gr.father(i));
    int q;inf.readargs(q);
    vector<int> col(n);
    cir(i,0,q){
        int op,u;inf.readargs(op,u);
        if(op==1){
            if(col[u]){
                bl.cut(u);
                wh.linkfa(u,gr.father(u));
            }else{
                wh.cut(u);
                bl.linkfa(u,gr.father(u));
            }
            col[u]^=1;
        }else{
            if(col[u]){
                const auto vx=bl.getanc(u);
                cout<<bl.subsize(gr.getchild(u,vx))<<'\n';
            }else{
                const auto vx=wh.getanc(u);
                cout<<wh.subsize(gr.getchild(u,vx))<<'\n';
            }
        }
    }
    return 0;
}
