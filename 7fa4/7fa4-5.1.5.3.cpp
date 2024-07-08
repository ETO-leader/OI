#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
using point=complex<lf>;
using vector_t=complex<lf>;
static constexpr auto eps=1e-20l;
auto cross(vector_t a,vector_t b){
    return (conj(a)*b).imag();
}
auto area(point a,point b,point c){
    return cross(b-a,c-a)/2;
}
constexpr auto invaild(point a){
    return isnan(a.real())||isnan(a.imag());
}
constexpr auto iszero(lf a){
    return fabsl(a)<eps;
}
constexpr auto same(lf a,lf b){
    return iszero(a-b);
}
class line{
private:
    point u;vector_t v;
public:
    auto chkpoint(const line l) const{
        const auto pa=u,pb=u+v,pc=l.u,pd=l.u+l.v;
        const auto ara=area(pa,pc,pd),arb=area(pb,pd,pc);
        return (pa*arb+pb*ara)/(ara+arb);
    }
    auto check(const point a) const{return cross(v,a-u);}
    auto argx() const{return arg(v);}
    auto parallel(const line l) const{return iszero(cross(v,l.v));}
    auto left(const line l) const{return cross(l.v,u-l.u)>eps;}
    line(point a,point b):u(a),v(b-a){}
};
template<typename _Ty>
auto chkarea(_Ty ps){
    ps.push_back(ps.front());
    auto res=0.0l;
    cir(i,0,(int)(ps.size())-1) res+=cross(ps[i],ps[i+1])/2;
    return res;
}
auto check(vector<line> qx){
    sort(qx.begin(),qx.end(),[&](line&a,line&b){
        return a.argx()<b.argx();
    });
    deque<line> q;deque<point> m;
    q.push_back(qx[0]);
    qx.erase(qx.begin());
    for(auto&l:qx){
        while((!m.empty())&&l.check(m.back())<0)
            q.pop_back(),m.pop_back();
        if(l.parallel(q.back())){
            if(l.left(q.back())){
                q.back()=l;
                if(!m.empty()) m.back()=prev(q.end(),2)->chkpoint(l);    
            }
        }else{
            q.push_back(l);
            m.push_back(prev(q.end(),2)->chkpoint(l));
        }
    }
    while(!m.empty()){
        if(q.front().check(m.back())<0)
            q.pop_back(),m.pop_back();
        else if(q.back().check(m.front())<0)
            q.pop_front(),m.pop_front();
        else break;
    }
    m.push_back(q.front().chkpoint(q.back()));
    return chkarea(m);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<line> a;
    cir(i,0,n){
        int ni;cin>>ni;
        vector<point> px;
        cir(c,0,ni){
            lf xi,yi;cin>>xi>>yi;
            px.push_back({xi,yi});
        }
        cir(c,0,ni) a.push_back(line(px[c],px[(c+1)%ni]));
    }
    cout<<fixed<<setprecision(15)<<check(a)<<'\n';
    return 0;
}
