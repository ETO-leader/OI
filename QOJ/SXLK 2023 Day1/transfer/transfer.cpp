#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifndef ONLINE_JUDGE
ifstream inf("transfer.in");
ofstream ouf("transfer.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
#else
#define inf cin
#define ouf cout
#endif
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
template<typename node_type,class updater,class push_downer,class maintainer,class null>
class segment{
private:
    vector<node_type> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto updaten(int u,int l,int r,int ql,int qr,auto...w){
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr) return updater::update(tr[u],w...);
        const auto mid=(l+r)/2;
        push_downer::push_down(tr[u],tr[ls(u)],tr[rs(u)]);
        updaten(ls(u),l,mid,ql,qr,w...);
        updaten(rs(u),mid+1,r,ql,qr,w...);
        tr[u]=maintainer::merge(tr[ls(u)],tr[rs(u)]);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(r<ql||qr<l) return null::make_null();
        if(ql-1<l&&r-1<qr) return tr[u];
        const auto mid=(l+r)/2;
        push_downer::push_down(tr[u],tr[ls(u)],tr[rs(u)]);
        return maintainer::merge(query(ls(u),l,mid,ql,qr),query(rs(u),mid+1,r,ql,qr));
    }
    const int n;
public:
    auto update(int l,int r,auto...w){
        updaten(1,0,n-1,l,r,w...);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n):n(_n),tr(_n<<2){}
};
using min_type=pair<int,int>;
class min_updater{
public:
    static auto update(auto&a,auto&b){a=b;}
};
class min_push_downer{
public:
    static auto push_down(auto&...args){}
};
class min_maintainer{
public:
    static auto merge(auto x,auto y){return min(x,y);}
};
class min_null{
public:
    static auto make_null(){return min_type(_inf,_inf);}
};
class sum_type{
public:
    int tag;
    tuple<int,int,int> mn;
    sum_type(int _tag=0,tuple<int,int,int> _mn={_inf,-1,-1}):tag(_tag),mn(_mn){}
};
class sum_updater{
public:
    static auto update(auto&a,auto&b){
        // clog<<"$ "<<a.tag<<" + "<<b.tag<<'\n';
        a.tag+=b.tag;get<0>(a.mn)+=b.tag;
    }
    static auto update(auto&a,auto&b,auto _copy){a=b;}
};
class sum_push_downer{
public:
    static auto push_down(auto&u,auto&ls,auto&rs){
        sum_updater::update(ls,u);
        sum_updater::update(rs,u);
        u.tag=0;
    }
};
class sum_maintainer{
private:
    static auto clear(auto&x){
        x.tag=0;return x;
    }
public:
    static auto merge(auto x,auto y){return clear(x.mn<y.mn?x:y);}
};
class sum_null{
public:
    static auto make_null(){return sum_type(0,make_tuple(_inf,_inf,_inf));}
};
class tree{
private:
    vector<vector<int>> gr;
    vector<int> dfn,rdfn,idfn,siz,top,fr,dep;
    segment<min_type,min_updater,min_push_downer,min_maintainer,min_null> sub;
    segment<sum_type,sum_updater,sum_push_downer,sum_maintainer,sum_null> path;
    lint ans;
    vector<multiset<int>> val;
    enum op_type{make_leeks,destroy_staff};
    struct operation{
        op_type op;
        int u,w;
        operation(op_type _op,int _u,int _w):op(_op),u(_u),w(_w){}
    };
    vector<vector<operation>> ops;
    auto init(int u,int f=-1)->int{
        siz[u]=1;fr[u]=f;
        dep[u]=(f>-1?dep[f]+1:0);
        for(auto&i:gr[u]) siz[u]+=init(i,u);
        sort(gr[u].begin(),gr[u].end(),[&](auto u,auto v){
            return siz[u]>siz[v];
        });
        return siz[u];
    }
    auto dfs(int u,auto&cnt)->void{
        idfn[dfn[u]=++cnt]=u;
        sub.update(dfn[u],dfn[u],min_type(0,u));
        path.update(dfn[u],dfn[u],sum_type(0,make_tuple(0,-dep[u],u)),true);
        val[u].emplace(0);
        val[u].emplace(_inf);
        for(auto&i:gr[u]) dfs(i,cnt);
        rdfn[u]=cnt;
    }
    auto init_path(int u,int utop=-1){
        if(utop<0) utop=u;
        top[u]=utop;
        if(gr[u].empty()) return;
        init_path(gr[u][0],utop);
        for(auto&i:gr[u]) if(i!=gr[u][0]) init_path(i);
    }
    auto path_update(int u,int w){
        for(;u>-1;u=fr[top[u]]) path.update(dfn[top[u]],dfn[u],sum_type(w));
    }
    auto nearest(int u){
        for(;u>-1;u=fr[top[u]]){
            const auto[w,dep,v]=path.query(dfn[top[u]],dfn[u]).mn;
            if(!w) return v;
        }
        return u;
    }
    auto leeks(int u,int w,const bool version=true){
        ans+=w;
        if(version) ops.back().emplace_back(make_leeks,u,w);
        val[u].emplace(w);
        sub.update(dfn[u],dfn[u],min_type(*val[u].begin(),u));
        path_update(u,-1);
    }
    auto destroy(int u,int w,const bool version=true){
        ans-=w;
        if(version) ops.back().emplace_back(destroy_staff,u,w);
        val[u].erase(val[u].find(w));
        sub.update(dfn[u],dfn[u],min_type(*val[u].begin(),u));
        path_update(u,1);
    }
public:
    auto link(int u,int f){
        gr[f].emplace_back(u);
    }
    auto init(){
        auto cnt=-1;init(0);dfs(0,cnt);init_path(0);
    }
    auto emplace(int u,int w){
        const auto v=nearest(u);
        ops.emplace_back();
        if(v<0){
            leeks(u,w);
        }else{
            const auto[wp,p]=sub.query(dfn[v],rdfn[v]);
            if(wp<w){
                destroy(p,wp);
                leeks(u,w);
            }
        }
    }
    auto roll_back(){
        for(auto&[op,u,w]:ops.back()){
            op==make_leeks?destroy(u,w,false):leeks(u,w,false);
        }
        ops.pop_back();
    }
    auto current(){return ans;}
    tree(int _n):gr(_n),idfn(_n),rdfn(_n),dfn(_n),dep(_n),fr(_n),siz(_n),top(_n),val(_n),sub(_n),path(_n),ans(0){}
};
class divide_structure{
private:
    vector<vector<pair<int,int>>> tr;
    vector<lint> ans;
    tree*cur;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto update(int u,int l,int r,int ql,int qr,int ux,int wx){
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr) return tr[u].emplace_back(ux,wx),void();
        const auto mid=(l+r)/2;
        update(ls(u),l,mid,ql,qr,ux,wx);
        update(rs(u),mid+1,r,ql,qr,ux,wx);
    }
    auto enter(int u){
        for(auto&[ux,wx]:tr[u]) cur->emplace(ux,wx);
    }
    auto leave(int u){
        cir(i,0,(int)(tr[u].size())) cur->roll_back();
    }
    auto divide(int u,int l,int r){
        enter(u);
        if(l==r) return ans[l]=cur->current(),leave(u);
        const auto mid=(l+r)/2;
        divide(ls(u),l,mid);divide(rs(u),mid+1,r);
        leave(u);
    }
    const int n;
public:
    auto update(int l,int r,int u,int w){
        update(1,0,n-1,l,r,u,w);
    }
    auto divide(){
        divide(1,0,n-1);
        return ans;
    }
    divide_structure(int _n,tree*_cur):tr(_n<<2),ans(_n),n(_n),cur(_cur){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int sid;inf>>sid;
    int n,k,m;inf>>n>>k>>m;
    tree tr(n);
    cir(i,1,n){
        int f;inf>>f;--f;tr.link(i,f);
    }
    tr.init();
    divide_structure sg(m+1,&tr);
    vector<int> inq(k+m),ddl(k+m,m);
    vector<pair<int,int>> info;
    cir(i,0,k){
        int u,w;inf>>u>>w;--u;
        inq[info.size()]=0;
        info.emplace_back(u,w);
    }
    cir(i,0,m){
        int op;inf>>op;
        if(op==1){
            int u,w;inf>>u>>w;--u;
            inq[info.size()]=i+1;
            info.emplace_back(u,w);
        }else{
            int id;inf>>id;--id;
            ddl[id]=i;
        }
    }
    cir(i,0,(int)(info.size())) sg.update(inq[i],ddl[i],info[i].first,info[i].second);
    const auto ans=sg.divide();
    for(auto&i:ans) ouf<<i<<' ';
    ouf<<'\n';
    return 0;
}
