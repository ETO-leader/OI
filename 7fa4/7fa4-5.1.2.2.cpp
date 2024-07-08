#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
using point=complex<__int128_t>;
using vector_t=complex<__int128_t>;
auto dot(vector_t a,vector_t b){
    return (a*conj(b)).real();
}
auto cross(vector_t a,vector_t b){
    return (a*conj(b)).imag();
}
template<typename _Ty>
constexpr auto x(complex<_Ty> p){
    return p.real();
}
template<typename _Ty>
constexpr auto y(complex<_Ty> p){
    return p.imag();
}
constexpr auto absq(__int128_t x){
    return x<0?-x:x;
}
auto area(const vector<point>&ps){
    auto res=(__int128_t)(0);
    const auto len=(int)(ps.size());
    cir(i,0,len) res+=cross(ps[i],ps[(i+1)%len]);
    return absq(res)*0.5l;
}
auto centerg(const vector<point>&ps){
    auto res=point(0,0),smw=point(0,0);
    const auto len=(int)(ps.size());
    cir(i,0,len) res+=cross(ps[i],ps[(i+1)%len])*(ps[i]+ps[(i+1)%len]);
    cir(i,0,len) smw+=cross(ps[i],ps[(i+1)%len]);
    return complex<lf>(x(res),y(res))*(1/3.0l)/complex<lf>(x(smw),y(smw));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<point> ps(n);
    for(auto&i:ps){
        int xi,yi;cin>>xi>>yi;
        i=point(xi,yi);
    }
    const auto ar=area(ps);
    const auto cg=centerg(ps);
    cout<<fixed<<setprecision(15)<<ar<<' '<<x(cg)<<' '<<y(cg)<<'\n';
    return 0;
}