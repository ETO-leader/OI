#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e12l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<lint> p(n);
    for(auto&i:p) cin>>i;
    cir(i,1,n) p[i]+=p[i-1];
    vector<lint> xi(m);
    for(auto cnt=-1;auto&i:xi) cin>>i;
    xi.insert(xi.begin(),-_infl);
    xi.push_back(_infl*2);
    ranges::sort(xi);
    auto vaild=[&](int l,int r){
        if(l>r) return true;
        if(ranges::lower_bound(xi,l*100)!=ranges::upper_bound(xi,r*100)) return false;
        const auto dl=l*100-*prev(ranges::lower_bound(xi,l*100))-1,dr=*ranges::lower_bound(xi,r*100)-100*r-1;
        return dl+dr+2>(r-l)*100;
    };
    auto ans=0ll;
    auto l=0;
    cir(r,0,n){
        while(!vaild(l,r)) ++l;
        ans=max(ans,p[r]-(l?p[l-1]:0));
    }
    println("{}",ans);
    return 0;
}
