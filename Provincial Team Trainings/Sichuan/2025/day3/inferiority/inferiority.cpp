#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("inferiority.in");
ofstream ouf("inferiority.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
using bdata=array<int,24>;
auto&operator+=(bdata&a,bdata b){
    cir(i,0,(int)(a.size())) a[i]+=b[i]; 
    return a;
}
auto operator+(bdata a,bdata b){
    return a+=b;
}
auto operator-(bdata a){
    for(auto&i:a) i=-i;
    return a;
}
template<typename _Ty>
class bit{
private:
    vector<_Ty> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
public:
    auto update(int u,_Ty x){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]+=x;
    }
    auto query(int u,auto res){
        for(u=min<int>(u+1,a.size()-1);u;u-=lowbit(u)) res+=a[u];
        return res;
    }
    bit(int _n):a(_n+1){}
};
class blocks{
private:
    struct block{
        vector<bdata> pre;
        block(int _n):pre(_n){}
    };
    vector<block> datas;
    vector<bdata> pre;
    const int len;
    const int n;
    constexpr auto blcof(auto u) const{return u/len;}
    constexpr auto blclef(auto u) const{return blcof(u)*len;}
public:
    auto update(int u,bdata ndata){
        const auto b=blcof(u);
        const auto p=blclef(u);
        cir(i,b,(int)(pre.size())) pre[i]+=ndata;
        cir(i,u-p,(int)(datas[b].pre.size())) datas[b].pre[i]+=ndata;
    }
    auto query(int u){
        u=min(u,n-1);
        const auto b=blcof(u);
        const auto p=blclef(u);
        if(!b) return datas[b].pre[u];
        return pre[b-1]+datas[b].pre[u-p];
    }
    blocks(int _n):n(_n),len(sqrt(_n)+1),datas(sqrt(_n)+7,block(sqrt(_n)+7)),pre(sqrt(_n)+7){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,q;inf>>n>>q;
    vector<int> a(n);
    for(auto&i:a) inf>>i;
    vector<tuple<int,int,int>> qry(q);
    for(auto c=-1;auto&[l,r,id]:qry) inf>>l>>r,--l,--r,id=++c;
    const auto sqr=(int)(sqrt(q));
    sort(qry.begin(),qry.end(),[&](auto&a,auto&b){
        return get<1>(a)/sqr==get<1>(b)/sqr?get<0>(a)<get<0>(b):get<1>(a)<get<1>(b);
    });
    vector<unordered_set<int>> ql(n),qr(n);
    const auto empty=[&]{
        bdata res;
        fill(res.begin(),res.end(),0);
        return res;
    }();
    [&]{
        auto l=0,r=-1;
        auto dec_l=[&](int target){
            if(l) qr[l-1].emplace(r);
            if(target) qr[target-1].emplace(r);
            l=target;
        };
        auto inc_r=[&](int target){
            if(l) ql[l-1].emplace(r);
            if(l) ql[l-1].emplace(target);
            r=target;
        };
        auto inc_l=[&](int target){
            if(l) qr[l-1].emplace(r);
            if(target) qr[target-1].emplace(r);
            l=target;
        };
        auto dec_r=[&](int target){
            if(l) ql[l-1].emplace(r);
            if(l) ql[l-1].emplace(target);
            r=target;
        };
        for(auto&[ql,qr,qid]:qry){
            if(r<qr) inc_r(r);
            if(ql<l) dec_l(l);
            if(qr<r) dec_r(r);
            if(l<ql) inc_l(l);
        }
    }();
    vector<lint> upre(n);
    vector<unordered_map<int,lint>> ansi(n);
    [&]{
        vector<bdata> ux(n);
        cir(i,0,n) cir(c,0,24) ux[i][c]=((a[i]>>c)&1);
        bit<int> nums(n+7);
        blocks cur(n+7);
        auto all=empty;
        cir(i,0,n){
            cur.update(a[i],ux[i]);
            nums.update(a[i],1);
            all+=ux[i];
            for(auto&p:needed[i]){
                const auto _v=a[p];
                const auto lb=(_v-1)/2;
                const auto ub=_v*2;
                const auto inrange=all+(-cur.query(ub))+cur.query(lb);
                const auto inrange_c=(i+1)-nums.query(ub,0)+nums.query(lb,0);
                cir(x,0,24){
                    if((_v>>x)&1) ansi[i][p]+=(lint)(inrange_c-inrange[x])<<x;
                    else ansi[i][p]+=(lint)(inrange[x])<<x;
                }
            }
        }
    }();
    vector<lint> uans(q);
    [&]{
        auto l=0,r=-1;
        auto ans=0ll;
        auto ins=[&](int p){
            ans+=ansi[r][p];
            if(l) ans-=ansi[l-1][p];
        };
        auto rmv=[&](int p){
            ans-=ansi[r][p];
            if(l) ans+=ansi[l-1][p];
        };
        for(auto&[ql,qr,qid]:qry){
            while(r<qr) ins(++r);
            while(ql<l) ins(--l);
            while(qr<r) rmv(r),--r;
            while(l<ql) rmv(l),++l;
            uans[qid]=ans;
        }
    }();
    for(auto&i:uans) ouf<<i<<'\n';
    return 0;
}
