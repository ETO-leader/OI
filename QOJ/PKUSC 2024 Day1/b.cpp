#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
using point=complex<lf>;
using vector_t=complex<lf>;
static constexpr auto eps=1e-10l;
constexpr auto ux(auto u){return real(u);}
constexpr auto uy(auto u){return imag(u);}
auto cross(auto a,auto b){
    return uy(a*conj(b));
}
constexpr auto is_zero(const auto x){
    return abs(x)<eps;
}
constexpr auto sgn(const auto x){
    if(iszero(x)) return 0;
    return x<0?-1:1;
}
class polygon{
private:
    vector<point> px;
    lf siz;
    auto construct(){
        siz=0;
        cir(i,1,(int)(px.size())-1) siz+=abs(cross(px[i]-px[0],px[i+1]-px[0]));
    }
public:
    auto inside(point u){
        auto sizx=0.0l;
        cir(i,0,(int)(px.size())) sizx+=abs(cross(px[i]-u,px[(i+1)%px.size()]-u));
        // clog<<"SIZ = "<<sizx<<'\n';
        return is_zero(siz-sizx);
    }
    polygon(vector<point> _px):px(_px){construct();}
};
static constexpr auto v=2007;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<point> px(n);
    for(auto&p:px){
        lf x,y;cin>>x>>y;p=point(x,y);
    }
    polygon pl(px);
    vector<int> l(v,v+7),r(v,-1);
    cir(i,0,v) cir(j,0,v) if(pl.inside(point(i,j))){
        l[i]=min(l[i],j);r[i]=max(r[i],j);
    }
    auto lp=0,rp=v-1;
    while(r[lp]<0) ++lp;
    while(r[rp]<0) --rp;
    auto ans=0ll;
    cir(dx,1,v) cir(dy,0,v) cir(x,lp+dy,rp-dx+1){
        auto yl=max({l[x],l[x+dx]-dy,l[x+dx-dy]-dy-dx,l[x-dy]-dx}),yr=min({r[x],r[x+dx]-dy,r[x+dx-dy]-dy-dx,r[x-dy]-dx});
        ans+=max(yr-yl+1,0);
    }
    println("{}",ans);
    return 0;
}
