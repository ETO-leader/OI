#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
using point=complex<lf>;
using vector_t=complex<lf>;
static constexpr auto eps=1e-20l;
auto dot(vector_t a,vector_t b){
    return (a*conj(b)).real();
}
auto cross(vector_t a,vector_t b){
    return (a*conj(b)).imag();
}
constexpr auto iszero(lf x){
    return fabsl(x)<eps;
}
constexpr auto type(lf x){
    return (!iszero(x))*(x>eps?1:-1);
}
auto simw(point a,point b,point c,point d){
    return cross(c-a,d-a)/cross(d-c,b-a);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<point> ps(n);
    for(auto&i:ps){
        int x,y;cin>>x>>y;i=point(x,y);
    }
    auto ans=0.0l;
    cir(i,0,n) cir(j,i+1,n){
        const auto u=ps[i],v=ps[j];
        vector<pair<lf,int>> qx;
        cir(x,0,n){
            const auto pu=ps[x],pv=ps[(x+1)%n];
            const auto px=type(cross(v-u,pu-u)),py=type(cross(v-u,pv-u));
            // No solution
            if(px==py) continue;
            qx.push_back({simw(u,v,pu,pv),(px<py?1:-1)*(1+(px&&py))});
        }
        sort(qx.begin(),qx.end());
        auto ansi=0.0l,ansq=0.0l;auto qw=0;
        cir(x,0,(int)(qx.size())){
            if(qw) ansi+=qx[x].first-qx[x-1].first;
            else ansq=max(ansq,ansi),ansi=0;
            qw+=qx[x].second;
        }
        ansq=max(ansq,ansi);
        ans=max(ans,ansq*abs(v-u));
    }
    cout<<fixed<<setprecision(15)<<ans<<'\n';
    return 0;
}
