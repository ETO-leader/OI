#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
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
        const auto n=readarg<int>();
        cir(i,0,n){
            const auto op=readarg<char>();
            if(op=='D') readarg<int>();
            else cir(i,0,4) readarg<int>();
        }
        cur=0;
    }
    auto iterator(){return cur;}
    auto seek(int x){cur=x;}
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
template<typename datatype,class initer,class maintainer>
struct nodetype{
    nodetype*ls,*rs;
    datatype data;
    auto maintain(){
        maintainer::clear(data);
        if(ls) maintainer::maintain(data,ls->data);
        if(rs) maintainer::maintain(data,rs->data);
    }
    nodetype():ls(nullptr),rs(nullptr),data(initer::default_val){}
};
template<class node,class initer,class allocer>
class segment{
    node*root;
    auto update(node*u,int l,int r,int p,auto...args){
        u->data.update(args...);
        if(l==r) return;
        const auto mid=(l+r)/2;
        if(p-1<mid&&(!u->ls)) u->ls=allocer::getnode();
        if(p>mid&&(!u->rs)) u->rs=allocer::getnode();
        p-1<mid?update(u->ls,l,mid,p,args...):update(u->rs,mid+1,r,p,args...);
        u->maintain();
    }
    auto query(node*u,int l,int r,int ql,int qr,auto...args){
        if((!u)||r<ql||qr<l||qr<ql) return initer::nontype;
        if(ql-1<l&&r-1<qr) return u->data.query(args...);
        const auto mid=(l+r)/2;
        return query(u->ls,l,mid,ql,qr,args...)+query(u->rs,mid+1,r,ql,qr,args...);
    }
    int n;
public:
    auto update(int p,auto...args){
        update(root,0,n-1,p,args...);
    }
    auto query(int l,int r,auto...args){
        return query(root,0,n-1,l,r,args...);
    }
    segment(int _n):n(_n){root=allocer::getnode();}
};
class intdata{
public:
    int sum;
    auto update(int w){sum+=w;}
    auto query(){return sum;}
    intdata(int _w):sum(_w){}
};
class intiniter{
public:
    static constexpr auto nontype=0;
    static constexpr auto default_val=0;
};
class intmaintainer{
public:
    static auto clear(intdata&x){x.sum=0;}
    static auto maintain(intdata&x,intdata&w){x.sum+=w.sum;}
};
template<const int maxn>
class seginiter{
public:
    static constexpr auto nontype=0;
    static constexpr auto default_val=maxn;
};
class segmaintainer{
public:
    static auto clear(auto&){}
    static auto maintain(auto&,auto&){}
};
static constexpr auto maxn=(int)(2e5+7);
namespace nodeallocers{
    static constexpr auto maxmem=(int)(3e7+7);
    array<nodetype<intdata,intiniter,intmaintainer>,maxmem> bn;
    int cur;
    class intallocer{
    public:
        static auto getnode(){return&(bn[++cur]=nodetype<intdata,intiniter,intmaintainer>());}
    };
    vector<nodetype<segment<nodetype<intdata,intiniter,intmaintainer>,intiniter,intallocer>,seginiter<maxn>,segmaintainer>*> rmv;
    class segallocer{
    public:
        static auto getnode(){
            rmv.emplace_back(new nodetype<segment<nodetype<intdata,intiniter,intmaintainer>,intiniter,intallocer>,seginiter<maxn>,segmaintainer>());
            return rmv.back();
        }
    };
    auto clearnode(){cur=(int)(5e6);}
    auto remove_roots(){for(auto&i:rmv) delete i;}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;inf.init();
    int n;inf.readargs(n);
    const auto sk=inf.iterator();
    segment<nodetype<intdata,intiniter,intmaintainer>,intiniter,nodeallocers::intallocer> sgl(maxn),sgr(maxn),sgd(maxn),sgu(maxn);
    segment<nodetype<segment<nodetype<intdata,intiniter,intmaintainer>,intiniter,nodeallocers::intallocer>,seginiter<maxn>,segmaintainer>,seginiter<maxn>,nodeallocers::segallocer>
        sgld(maxn),sglu(maxn),sgrd(maxn),sgru(maxn);
    vector<tuple<int,int,int,int>> k;
    map<int,int> idxq,idyq;
    cir(i,0,n){
        char op;inf.readargs(op);
        if(op=='I'||op=='Q'){
            int l,u,r,d;inf.readargs(l,u,r,d);
            idxq.emplace(l,0);idxq.emplace(r,0);
            idyq.emplace(u,0);idyq.emplace(d,0);
        }else{
            int id;inf.readargs(id);
        }
    }
    for(auto id=-1;auto&[a,b]:idxq) b=++id;
    for(auto id=-1;auto&[a,b]:idyq) b=++id;
    __gnu_pbds::gp_hash_table<int,int> idx,idy;
    for(auto&x:idxq) idx.insert(x);
    for(auto&x:idyq) idy.insert(x);
    auto curcnt=0;
    inf.seek(sk);
    vector<int> ans(n,-1);
    cir(i,0,n){
        char op;inf.readargs(op);
        if(op=='I'){
            int l,u,r,d;inf.readargs(l,u,r,d);
            l=idx[l];r=idx[r];u=idy[u];d=idy[d];
            k.emplace_back(l,r,u,d);++curcnt;
            sgl.update(l,1);
            sgr.update(r,1);
            sgd.update(d,1);
            sgu.update(u,1);
        }else if(op=='D'){
            int id;inf.readargs(id);--id;--curcnt;
            const auto[l,r,u,d]=k[id];
            sgl.update(l,-1);
            sgr.update(r,-1);
            sgd.update(d,-1);
            sgu.update(u,-1);
        }else{
            int l,u,r,d;inf.readargs(l,u,r,d);
            l=idx[l];r=idx[r];u=idy[u];d=idy[d];
            ans[i]=
                curcnt
                -sgl.query(r+1,maxn-1)
                -sgr.query(0,l-1)
                -sgu.query(d+1,maxn-1)
                -sgd.query(0,u-1);
        }
    }
    inf.seek(sk);
    nodeallocers::clearnode();
    cir(i,0,n){
        char op;inf.readargs(op);
        if(op=='I'){
            int l,u,r,d;inf.readargs(l,u,r,d);
            l=idx[l];r=idx[r];u=idy[u];d=idy[d];
            sgld.update(l,d,1);
        }else if(op=='D'){
            int id;inf.readargs(id);--id;
            const auto[l,r,u,d]=k[id];
            sgld.update(l,d,-1);
        }else{
            int l,u,r,d;inf.readargs(l,u,r,d);
            l=idx[l];r=idx[r];u=idy[u];d=idy[d];
            ans[i]+=sgld.query(r+1,maxn-1,0,u-1);
        }
    }
    inf.seek(sk);
    nodeallocers::clearnode();
    cir(i,0,n){
        char op;inf.readargs(op);
        if(op=='I'){
            int l,u,r,d;inf.readargs(l,u,r,d);
            l=idx[l];r=idx[r];u=idy[u];d=idy[d];
            sglu.update(l,u,1);
        }else if(op=='D'){
            int id;inf.readargs(id);--id;
            const auto[l,r,u,d]=k[id];
            sglu.update(l,u,-1);
        }else{
            int l,u,r,d;inf.readargs(l,u,r,d);
            l=idx[l];r=idx[r];u=idy[u];d=idy[d];
            ans[i]+=sglu.query(r+1,maxn-1,d+1,maxn-1);
        }
    }
    inf.seek(sk);
    nodeallocers::clearnode();
    cir(i,0,n){
        char op;inf.readargs(op);
        if(op=='I'){
            int l,u,r,d;inf.readargs(l,u,r,d);
            l=idx[l];r=idx[r];u=idy[u];d=idy[d];
            sgrd.update(r,d,1);
        }else if(op=='D'){
            int id;inf.readargs(id);--id;
            const auto[l,r,u,d]=k[id];
            sgrd.update(r,d,-1);
        }else{
            int l,u,r,d;inf.readargs(l,u,r,d);
            l=idx[l];r=idx[r];u=idy[u];d=idy[d];
            ans[i]+=sgrd.query(0,l-1,0,u-1);
        }
    }
    inf.seek(sk);
    nodeallocers::clearnode();
    cir(i,0,n){
        char op;inf.readargs(op);
        if(op=='I'){
            int l,u,r,d;inf.readargs(l,u,r,d);
            l=idx[l];r=idx[r];u=idy[u];d=idy[d];
            sgru.update(r,u,1);
        }else if(op=='D'){
            int id;inf.readargs(id);--id;
            const auto[l,r,u,d]=k[id];
            sgru.update(r,u,-1);
        }else{
            int l,u,r,d;inf.readargs(l,u,r,d);
            l=idx[l];r=idx[r];u=idy[u];d=idy[d];
            ans[i]+=sgru.query(0,l-1,d+1,maxn-1);
        }
    }
    for(auto&i:ans) if(i>-1) cout<<i<<'\n';
    nodeallocers::remove_roots();
    return 0;
}
