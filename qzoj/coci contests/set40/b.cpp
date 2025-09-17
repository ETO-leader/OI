#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    vector<int> a(n);
    map<int,int> ax;
    for(auto&i:a) cin>>i,ax.emplace(i,0);
    auto c=-1;
    for(auto&[x,y]:ax) y=++c;
    for(auto&x:a) x=ax[x];
    vector<tuple<int,int,int>> qx(q);
    c=-1;
    for(auto&[l,r,id]:qx) cin>>l>>r,id=++c,--l,--r;
    const auto sqr=max(n/(int)(sqrt(q+1)),1);
    sort(qx.begin(),qx.end(),[&](auto a,auto b){
        return get<0>(a)/sqr==get<0>(b)/sqr?get<1>(a)<get<1>(b):get<0>(a)<get<0>(b);
    });
    auto l=0,r=-1,uans=0;
    vector<int> cnt(n);
    auto upd=[&](int p){
        uans+=(cnt[a[p]]==1);
        uans-=(cnt[a[p]]==2);
        ++cnt[a[p]];
    };
    auto rmv=[&](int p){
        uans-=(cnt[a[p]]==2);
        uans+=(cnt[a[p]]==3);
        --cnt[a[p]];
    };
    vector<int> ans(q);
    for(auto&[ql,qr,id]:qx){
        while(r<qr) upd(++r);
        while(ql<l) upd(--l);
        while(r>qr) rmv(r--);
        while(ql>l) rmv(l++);
        ans[id]=uans;
    }
    for(auto&x:ans) cout<<x<<'\n';
    return 0;
}
