#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
using point=complex<lf>;
using vector_t=complex<lf>;
static constexpr auto eps=1e-20l;
static constexpr auto pi=acosl(-1);
auto cross(vector_t a,vector_t b){
    return (a*conj(b)).imag();
}
class line{
private:
    point u;vector_t v;
public:
    friend class circle;
    line(point a,point b):u(a),v(b-a){}
};
class circle{
private:
    point u;lf r;
public:
    auto check(const line l){
        return !(fabsl(cross(l.u-u,l.u+l.v-u)/abs(l.v))>r);
    }
    auto getpoint(vector_t angle){
        const auto rva=angle*complex<lf>(1i);
        return pair(u+rva*r,u-rva*r);
    }
    circle(point _u,lf _r=1):u(_u),r(_r){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<circle> crs;
    cir(i,0,n){
        lf xi,yi;cin>>xi>>yi;
        crs.push_back(circle(point(xi,yi)));
    }
    auto chk=[&](line x){
        auto res=0;
        for(auto&i:crs) res+=i.check(x);
        return res;
    };
    auto ans=0;
    for(auto i=0.0l;i<pi;i+=2e-3){
        const auto v=vector_t(cosl(i),sinl(i));
        for(auto&x:crs){
            const auto[px,py]=x.getpoint(v);
            ans=max({ans,chk(line(px,v)),chk(line(py,v))});
        }
    }
    for(auto i=pi;i>0;i-=2e-3){
        const auto v=vector_t(cosl(i),sinl(i));
        for(auto&i:crs){
            const auto[px,py]=i.getpoint(v);
            ans=max({ans,chk(line(px,v)),chk(line(py,v))});
        }
    }
    cout<<ans<<'\n';
    return 0;
}
