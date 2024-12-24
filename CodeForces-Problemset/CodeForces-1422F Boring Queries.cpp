#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;i++)
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
        const auto n=readarg<int>();
        cir(i,0,n) readarg<int>();
        const auto q=readarg<int>();
        cir(i,0,q*2) readarg<int>();
    }
    auto readargs(int&x){x=data[pos++].i32;}
    auto readargs(auto&...args){
        (readargs(args),...);
    }
    casereader():pos(0){}
};
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto a){return qpow(a,MOD-2);}
    auto primes(int n){
        vector<int> p,isp(n,true);
        cir(i,2,n) if(isp[i]){
            p.emplace_back(i);
            for(auto j=i*2;j<n;j+=i) isp[j]=false;
        }
        return p;
    }
} math;
template<const size_t maxmem>
class segment{
private:
    struct node{
        int ls,rs,prod;
        node():ls(0),rs(0),prod(1){}
    };
    array<node,maxmem> tr;
    int cnt;
    auto newnode(){
        tr[++cnt]=node();
        return cnt;
    }
    auto copy(int u){
        if(!u) return newnode();
        auto res=newnode();
        return tr[res]=tr[u],res;
    }
    auto maintain(node*u){
        u->prod=1;
        for(auto v:{u->ls,u->rs}) if(v) u->prod=((lint)(u->prod)*tr[v].prod)%MOD;
    }
    auto update(int&u,int l,int r,int p,lint w){
        u=copy(u);
        const auto ux=&tr[u];
        if(l==r) return ux->prod=ux->prod*w%MOD,void();
        const auto mid=(l+r)/2;
        p-1<mid?update(ux->ls,l,mid,p,w):update(ux->rs,mid+1,r,p,w);
        maintain(ux);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if((!u)||r<ql||qr<l) return 1ll;
        const auto ux=&tr[u];
        if(ql-1<l&&r-1<qr) return (lint)(ux->prod);
        const auto mid=(l+r)/2;
        return query(ux->ls,l,mid,ql,qr)*query(ux->rs,mid+1,r,ql,qr)%MOD;
    }
    int n;
    vector<int> vx;
public:
    auto update(int p,lint w){
        update(vx.back(),0,n-1,p,w);
    }
    auto query(int _v,int l,int r){
        return query(vx[_v],0,n-1,l,r);
    }
    auto makecopy(){
        vx.push_back(copy(vx.back()));
    }
    segment(int _n):n(_n),cnt(0),vx({0}){}
};
class mxsegment{
private:
    vector<int> mx;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto build(int u,int l,int r,vector<int>&a){
        if(l==r) return mx[u]=a[l],void();
        const auto mid=(l+r)/2;
        build(ls(u),l,mid,a);
        build(rs(u),mid+1,r,a);
        mx[u]=max(mx[ls(u)],mx[rs(u)]);
    }
    auto query(int u,int l,int r,int ql,int qr,int&cur){
        if(r<ql||qr<l||mx[u]<cur+1) return 0;
        if(ql-1<l&&r-1<qr) return cur=max(cur,mx[u]);
        const auto mid=(l+r)/2;
        return max(query(ls(u),l,mid,ql,qr,cur),query(rs(u),mid+1,r,ql,qr,cur));
    }
    int n;
public:
    auto init(vector<int> a){
        build(1,0,(int)(a.size())-1,a);
    }
    auto query(int l,int r){
        int cur=0;
        return query(1,0,n-1,l,r,cur);
    }
    mxsegment(int _n):n(_n),mx(_n<<2){}
};
static constexpr auto maxmem=(int)(1e7+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;inf.init();
    int n;inf.readargs(n);
    vector<int> a(n);
    for(auto&i:a) inf.readargs(i);
    const auto pr=math.primes((int)(sqrt(*max_element(a.begin(),a.end())))+7);
    const auto p=(int)(pr.size());
    vector<vector<int>> w(p,vector<int>(n));
    for(auto i=-1;auto&x:pr){
        ++i;
        cir(p,0,n){
            auto cnt=0;
            while(!(a[p]%x)) a[p]/=x,++cnt;
            w[i][p]=cnt;
        }
    }
    vector<mxsegment> sgs(p,mxsegment(n));
    cir(i,0,p) sgs[i].init(w[i]);
    segment<maxmem> sg(n);
    vector<int> las(*max_element(a.begin(),a.end())+7,-1);
    cir(i,0,n){
        if(las[a[i]]>-1) sg.update(las[a[i]],math.inv(a[i]));
        las[a[i]]=i;
        sg.update(i,a[i]);
        sg.makecopy();
    }
    int q;inf.readargs(q);
    auto ans=0ll;
    cir(c,0,q){
        int l,r;inf.readargs(l,r);
        l=(l+ans)%n;r=(r+ans)%n;
        if(l>r) swap(l,r);
        ans=1ll;
        for(auto i=-1;auto&x:pr){
            ++i;
            (ans*=math.qpow(x,sgs[i].query(l,r)))%=MOD;
        }
        (ans*=sg.query(r,l,r))%=MOD;
        println("{}",ans);
    }
    return 0;
}
