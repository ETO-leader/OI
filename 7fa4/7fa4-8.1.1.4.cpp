#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class casereader{
private:
    union datatype{
        int i32;
        datatype(int x):i32(x){}
    };
    vector<datatype> data;
    int pos;
    template<typename _Ty>
    auto readarg(){
        _Ty x;cin>>x;data.emplace_back(x);
        return x;
    }
public:
    auto init(){
        const auto n=readarg<int>(),q=readarg<int>();
        cir(i,0,n*3+q*4) readarg<int>();
    }
    auto readargs(int&x){
        x=data[pos].i32;++pos;
    }
    auto readargs(auto&...args){
        (readargs(args),...);
    }
    casereader():pos(0){}
};
class segment{
private:
    struct node{
        shared_ptr<node> ls,rs;
        lint siz,sum;
        auto lsiz() const{return ls?ls->siz:0;}
        auto rsiz() const{return rs?rs->siz:0;}
        auto lsum() const{return ls?ls->sum:0;}
        auto rsum() const{return rs?rs->sum:0;}
        node():ls(nullptr),rs(nullptr),siz(0),sum(0){}
    };
    using pnode=shared_ptr<node>;
    auto copy(pnode u){
        if(!u) return make_shared<node>();
        auto v=make_shared<node>();*v=*u;
        return v;
    }
    auto update(pnode&u,int l,int r,int p,int w){
        u=copy(u);
        u->sum+=w*p;u->siz+=w;
        if(l==r) return;
        const auto mid=(l+r)/2;
        p-1<mid?update(u->ls,l,mid,p,w):update(u->rs,mid+1,r,p,w);
    }
    auto query(pnode u,int l,int r,int rk){
        if(!u) return 0ll;
        if(l==r) return (lint)(rk)*l;
        const auto mid=(l+r)/2;
        return rk<u->lsiz()+1?query(u->ls,l,mid,rk):query(u->rs,mid+1,r,rk-u->lsiz())+u->lsum();
    }
    vector<pnode> vx;
    int n;
public:
    auto update(int p,int w){
        update(vx.back(),0,n-1,p,w);
    }
    auto makecopy(){
        vx.push_back(copy(vx.back()));
    }
    auto query(int _v,int rk){
        return query(vx[_v],0,n-1,rk);
    }
    segment(int _n):n(_n),vx({nullptr}){}
};
static constexpr auto maxv=(int)(1e7+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;inf.init();
    int n,q;inf.readargs(n,q);
    vector<vector<pair<int,int>>> upd(q+1);
    cir(i,0,n){
        int s,e,w;inf.readargs(s,e,w);
        --s;
        upd[s].emplace_back(w,1);
        upd[e].emplace_back(w,-1);
    }
    segment sg(maxv);
    cir(i,0,q){
        for(auto&[p,w]:upd[i]) sg.update(p,w);
        sg.makecopy();
    }
    auto lasans=1ll;
    cir(i,0,q){
        int x,a,b,c;inf.readargs(x,a,b,c);
        --x;lasans%=c;
        const auto rk=(a*lasans+b)%c+1;
        cout<<(lasans=sg.query(x,rk))<<'\n';
    }
    return 0;
}
