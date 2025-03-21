#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class bit{
private:
    vector<lint> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
public:
    auto update(int u,lint w){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]+=w;
    }
    auto query(int u){
        auto res=0ll;
        for(++u;u;u-=lowbit(u)) res+=a[u];
        return res;
    }
    bit(int _n):a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;vector<int> a(n);
    for(auto&i:a) cin>>i,--i;
    vector<tuple<int,int,int,int>> qx(q);
    const auto sqr=(int)(n/sqrt(q));
    for(auto c=-1;auto&[l,r,id,d]:qx) cin>>l>>r,--l,--r,id=++c,d=l/sqr;
    vector<lint> prelss(n);
    bit b(n);
    cir(i,0,n) b.update(a[i],1),prelss[i]=b.query(a[i]-1);
    vector<lint> cnt(n),sum(n);
    auto ans=0ll;
    auto ins=[&](int u,int sgn){
        ans+=sum[a[u]]*sgn;
        ans-=prelss[u]*cnt[a[u]]*sgn;
        ++cnt[a[u]];sum[a[u]]+=prelss[u];
    };
    auto rmv=[&](int u,int sgn){
        --cnt[a[u]];sum[a[u]]-=prelss[u];
        ans-=sum[a[u]]*sgn;
        ans+=prelss[u]*cnt[a[u]]*sgn;
    };
    ranges::sort(qx,[sqr](auto&a,auto&b){
        return get<3>(a)==get<3>(b)?get<1>(a)<get<1>(b):get<0>(a)<get<0>(b);
    });
    auto l=0,r=-1;
    vector<lint> ax(q);
    for(auto&[ql,qr,id,d]:qx){
        while(r<qr) ins(++r,-1);
        while(l>ql) ins(--l,1);
        while(r>qr) rmv(r--,-1);
        while(l<ql) rmv(l++,1);
        ax[id]=ans;
    }
    for(auto&i:ax) cout<<i<<'\n';
    return 0;
}
