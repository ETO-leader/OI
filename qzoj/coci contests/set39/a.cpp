#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto eps=1e-6l;
static constexpr auto mulnum=(int)(1e8);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;lint a,b;cin>>n>>a>>b;
    vector<lint> w(n);
    set<lint> inside;
    for(auto&x:w){
        long double c;cin>>c;
        x=c*mulnum+eps;
        inside.emplace(x);
    }
    const auto sw=inside;
    a*=mulnum;
    b*=mulnum;
    set<lint> xw;
    cir(i,0,n) cir(j,0,n){
        const auto xa=w[i]/__gcd(w[i],w[j]);
        const auto xb=w[j]/__gcd(w[i],w[j]);
        if(abs(xa-xb)==1) xw.emplace(__gcd(w[i],w[j]));
    }
    for(auto&i:w) xw.emplace(i);
    vector<lint> ans;
    while(!inside.empty()){
        auto mx=make_pair(-1,0ll);
        for(auto&x:xw) [&]{
            const auto l=((a+x-1)/x)*x;
            const auto r=(b/x)*x;
            auto cnt=0;
            for(auto u=l;u<r+1;u+=x){
                if(!sw.count(u)) return;
                cnt+=inside.count(u);
            }
            mx=max(mx,{cnt,x});
        }();
        const auto x=mx.second;
        ans.emplace_back(x);
        [&]{
            const auto l=((a+x-1)/x)*x;
            const auto r=(b/x)*x;
            for(auto u=l;u<r+1;u+=x) if(inside.count(u)) inside.erase(u);
        }();
    }
    for(auto&x:ans) cout<<fixed<<setprecision(15)<<x*1.0l/mulnum<<'\n';
    return 0;
}
