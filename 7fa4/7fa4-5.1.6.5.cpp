#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=double;
using point=complex<lf>;
using vector_t=complex<lf>;
static constexpr auto eps=1e-10;
static constexpr auto pi=acos(-1);
static constexpr auto maxrange=sqrt(2)/2;
auto cross(vector_t a,vector_t b){
    return (conj(a)*b).imag();
}
constexpr auto iszero(lf x){
    return abs(x)<eps;
}
constexpr auto sign(lf x){
    return (x<0?-1:1)*(!iszero(x));
}
class segment{
private:
    point u;vector_t v;
    auto distf(point p){
        return abs(cross(p-u,v))/abs(v);
    }
public:
    auto norm() const{return v*1i;}
    auto dist(point p){
        const auto vn=norm();
        const auto simple=sign(cross(vn,u-p))!=sign(cross(vn,u+v-p));
        return simple?distf(p):min(abs(p-u),abs(p-(u+v)));
    }
    auto pass(point p){
        return iszero(v.imag())&&u.real()<p.real()&&
            u.imag()>p.imag()&&(u+v).real()>p.real();
    }
    segment(point a,point b):u(a),v(b-a){
        if(a.real()>b.real()) u=b,v=a-b;
    }
    segment()=default;
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    for(int n,testcase=1;cin>>n&&n;++testcase){
        auto u=point(0,0);
        map<char,vector_t> mvx;
        mvx['U']=vector_t(0,1);
        mvx['D']=vector_t(0,-1);
        mvx['L']=vector_t(-1,0);
        mvx['R']=vector_t(1,0);
        vector<segment> sgms(n);
        auto mnx=0.0,mxx=0.0,mny=0.0,mxy=0.0;
        for(auto&i:sgms){
            mnx=min(mnx,u.real());
            mxx=max(mxx,u.real());
            mny=min(mny,u.imag());
            mxy=max(mxy,u.imag());
            lf x;char dir;cin>>x>>dir;
            const auto v=u+mvx[dir]*x;
            i=segment(u,v);u=v;
        }
        vector<pair<lf,point>> px;
        auto ans=0.0;
        auto check=[&](point p){
            auto mn=1e9;
            for(auto&i:sgms) mn=min(mn,i.dist(p));
            return mn;
        };
        cir(xi,mnx,mxx) cir(yi,mny,mxy){
            const auto p=point(xi+0.5,yi+0.5);
            auto st=false;auto mn=1e9;
            for(auto&i:sgms){
                mn=min(mn,i.dist(p));
                st^=i.pass(p);
            }
            if(st) px.push_back({mn,p}),ans=max(ans,mn);
        }
        sort(px.begin(),px.end(),[&](auto&a,auto&b){
            return a.first>b.first;
        });
        uniform_real_distribution rdarg(0.0,pi*2);
        uniform_real_distribution rdlen(0.0,maxrange);
        mt19937 rnd(random_device().operator()());
        vector<vector_t> adi;
        while(px.size()>150) px.pop_back();
        cir(i,0,(px.size()<120?100000:30000)){
            const auto argi=rdarg(rnd);
            adi.push_back(vector_t(cos(argi),sin(argi))*rdlen(rnd));
        }
        for(auto&[wi,p]:px){
            for(auto&vi:adi) ans=max(ans,check(p+vi));
        }
        cout<<fixed<<setprecision(2)<<"Case Number "
            <<testcase<<" radius is: "<<round((ans+(px.size()<120?0.001:0.0025))*100)/100<<'\n';
    }
    return 0;
}