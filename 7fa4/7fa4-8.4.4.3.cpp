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
        cir(i,0,n*2) readarg<int>();
        const auto q=readarg<int>();
        cir(i,0,q){
            if(readarg<int>()==2) cir(i,0,2) readarg<int>();
            else readarg<int>();
        }
    }
    auto readargs(int&x){
        x=ax[cur].i32;++cur;
    }
    auto readargs(auto&x,auto&...args){
        readargs(x);readargs(args...);
    }
    casereader():cur(0){}
};
static constexpr auto _inf=(int)(1e9+7);
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
        int ls,rs,fr,siz,mx,val;
        node():ls(0),rs(0),fr(0),siz(1),mx(-_inf),val(-_inf){}
    };
    vector<node> tr;
    unordered_map<int,int> fx;
    constexpr auto&ls(auto u){return tr[u].ls;}
    constexpr auto&rs(auto u){return tr[u].rs;}
    constexpr auto&fr(auto u){return tr[u].fr;}
    constexpr auto isrs(auto u){return rs(fr(u))==u;}
    constexpr auto getroot(auto u){
        for(;fr(u);u=fr(u));
        return u;
    }
    constexpr auto getfirst(auto u){
        for(u=getroot(u);ls(u);u=ls(u));
        return u;
    }
    constexpr auto getrank(auto u){
        auto res=tr[ls(u)].siz+1;
        for(;fr(u);u=fr(u)) if(isrs(u)) res+=tr[ls(fr(u))].siz+1;
        return res;
    }
    auto maintain(int u){
        tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+1;
        tr[u].mx=max({tr[ls(u)].mx,tr[rs(u)].mx,tr[u].val});
    }
    auto split(int u,int rk){
        if(!u) return pair(0,0);
        if(tr[ls(u)].siz>rk-1){
            const auto[ux,vx]=split(ls(u),rk);
            ls(u)=vx;
            if(vx) fr(vx)=u;
            fr(ux)=0;
            return maintain(u),pair(ux,u);
        }else{
            const auto[ux,vx]=split(rs(u),rk-tr[ls(u)].siz-1);
            rs(u)=ux;
            if(ux) fr(ux)=u;
            fr(vx)=0;
            return maintain(u),pair(u,vx);
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
    auto link(int u,int v){
        ++u;++v;
        fx[u]=v;
        const auto[al,ax]=split(getroot(u),getrank(u)-1);
        const auto[sub,ar]=split(getroot(u+n),getrank(u+n));
        merge(al,ar);
        const auto[lf,rg]=split(getroot(v+n),getrank(v+n)-1);
        merge(merge(lf,sub),rg);
    }
    auto cut(int u){
        ++u;
        fx.erase(u);
        const auto[lf,ax]=split(getroot(u),getrank(u)-1);
        const auto[sub,rg]=split(getroot(u+n),getrank(u+n));
        merge(lf,rg);
    }
    auto root(auto u){return getfirst(u+1)-1;}
    auto maxval(int u){
        ++u;
        const auto v=fx[u];cut(u-1);
        const auto res=tr[getroot(u)].mx;
        link(u-1,v-1);
        return res;
    }
    auto initvalue(int u,int w){
        ++u;
        const auto[lf,rx]=split(getroot(u),getrank(u)-1);
        const auto[ux,rg]=split(getroot(u),1);
        tr[ux].mx=tr[ux].val=w;
        merge(merge(lf,ux),rg);
    }
    ett(int _n):n(_n+3),tr(_n*2+7){
        tr[0].siz=0;
        cir(i,1,_n+1) merge(i,i+_n+3);
    }
};
class tree{
private:
    vector<vector<int>> gr,up;
    vector<int> dfn,rdfn;
    static constexpr auto ups=21;
    auto dfs(int u,auto&cdfn,int f=0)->void{
        up[u][0]=f;dfn[u]=++cdfn;
        cir(i,1,ups) up[u][i]=up[up[u][i-1]][i-1];
        for(auto&i:gr[u]) if(i!=f) dfs(i,cdfn,u);
        rdfn[u]=cdfn;
    }
    auto isancestor(int u,int v) const{
        return dfn[u]<dfn[v]&&rdfn[v]-1<rdfn[u];
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto init(){
        auto cx=-1;dfs(0,cx);
    }
    auto ancdir(int u,int v){
        for(auto i=ups-1;~i;--i) if(isancestor(v,up[u][i])) u=up[u][i];
        return u;
    }
    auto father(auto u){return up[u][0];}
    tree(int _n):gr(_n),up(_n,vector<int>(ups)),dfn(_n),rdfn(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;inf.init();
    int n;inf.readargs(n);
    tree tr(n+1);
    tr.link(0,1);
    cir(i,0,n-1){
        int u,v;inf.readargs(u,v);
        tr.link(u,v);
    }
    tr.init();
    ++n;
    ett bl(n),wh(n);
    vector<int> col(n);
    cir(i,1,n){
        inf.readargs(col[i]);
        if(col[i]) bl.link(i,tr.father(i));
        else wh.link(i,tr.father(i));
    }
    cir(i,1,n){
        int w;inf.readargs(w);
        bl.initvalue(i,w);wh.initvalue(i,w);
    }
    int q;inf.readargs(q);
    cir(i,0,q){
        int op;inf.readargs(op);
        if(!op){
            int u;inf.readargs(u);
            const auto vx=(col[u]?bl:wh).root(u);
            const auto ax=tr.ancdir(u,vx);
            cout<<(col[u]?bl:wh).maxval(ax)<<'\n';
        }else if(op==1){
            int u;inf.readargs(u);
            (col[u]?bl:wh).cut(u);
            (col[u]?wh:bl).link(u,tr.father(u));
            col[u]^=true;
        }else{
            int u,w;inf.readargs(u,w);
            wh.initvalue(u,w);
            bl.initvalue(u,w);
        }
    }
    return 0;
}
