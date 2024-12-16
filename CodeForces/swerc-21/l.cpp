#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
using point=complex<lf>;
static constexpr auto _inf=(int)(1e9+7);
class bit{
private:
    vector<int> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
public:
    auto update(int u,int w){
        for(++u;u;u-=lowbit(u)) a[u]=max(a[u],w);
    }
    auto query(int u){
        auto res=0;
        for(++u;u<(int)(a.size());u+=lowbit(u)) res=max(res,a[u]);
        return res;
    }
    bit(int _n):a(_n+1,-_inf){}
};
static constexpr auto eps=(lf)(1e-10l);
constexpr auto fitlf(auto x){
    return roundl(x*1e6l);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,v;cin>>n>>v;
    vector<lf> x(n),y(n);
    for(auto&i:x) cin>>i,i*=v;
    for(auto&i:y) cin>>i;
    vector<point> px(n);
    for(auto cnt=-1;auto&i:px) ++cnt,i=point(x[cnt],y[cnt]);
    const auto arg=-numbers::pi/4;
    auto rotate=[&](point p){
        const auto[cx,cy]=pair(real(p),imag(p));
        const auto x=cosl(arg)*cx-sinl(arg)*cy;
        const auto y=cosl(arg)*cy+sinl(arg)*cx;
        return point(x,y);
    };
    const auto cpx=px;px.clear();
    for(auto&i:cpx) if(!(imag(i)>real(i))) px.emplace_back(i);
    for(auto&i:px) i=rotate(i);
    map<lf,int> idy;
    for(auto&i:px) idy.emplace(fitlf(imag(i)),0);
    for(auto c=-1;auto&[a,b]:idy) b=++c;
    vector<pair<lf,int>> ax;
    for(auto&i:px) ax.emplace_back(real(i),idy[fitlf(imag(i))]);
    ranges::sort(ax,[](auto&a,auto&b){
        return abs(a.first-b.first)<eps?a.second>b.second:a.first<b.first;
    });
    auto ans=0;
    bit f(n+7);f.update(0,0);
    for(auto&[x,y]:ax){
        const auto fx=f.query(y)+1;
        f.update(y,fx);
        ans=max(ans,fx);
    }
    println("{}",ans);
    return 0;
}
