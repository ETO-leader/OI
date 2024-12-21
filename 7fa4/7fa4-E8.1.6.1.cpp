#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class casereader{
private:
    union datatype{
        int i32;
        datatype(int x):i32(x){}
    };
    vector<datatype> ax;
    int cur;
    template<typename _Ty>
    auto readarg(){
        _Ty x;cin>>x;ax.emplace_back(x);
        return x;
    }
public:
    auto init(){
        const auto n=readarg<int>(),q=readarg<int>();
        cir(i,0,n*2) readarg<int>();
        cir(i,0,q*3) readarg<int>();
    }
    auto iterator(){return cur;}
    auto fseek(auto x){cur=x;}
    auto readargs(int&x){
        x=ax[cur].i32;++cur;
    }
    auto readargs(auto&x,auto&...args){
        readargs(x);readargs(args...);
    }
    casereader():cur(0){}
};
class point{
public:
    int x,y;
    point(int _x,int _y):x(_x),y(_y){}
};
// l < r | u < d
class rectangle{
private:
    int l,r,u,d;
public:
    auto operator&(const rectangle x) const{
        return !(r<x.l||x.r<l||d<x.u||x.d<u);
    }
    auto operator&(const point x) const{
        return rectangle(x.x,x.x,x.y,x.y)&(*this);
    }
    auto operator<(const rectangle x) const{
        return x.l<l+1&&r-1<x.r&&x.u<u+1&&d-1<x.d;
    }
    rectangle(int _l,int _r,int _u,int _d):l(_l),r(_r),u(_u),d(_d){}
};
static constexpr auto _inf=(int)(1e8+7);
static const auto cmpso=array{
    function<bool(point&,point&)>([](point&a,point&b){return a.x<b.x;}),
    function<bool(point&,point&)>([](point&a,point&b){return a.y<b.y;})
};
template<class comp>
class kdtree{
private:
    struct node{
        rectangle rng;int mx;
        node():rng(-1,-1,-1,-1),mx(max(-_inf,_inf,comp())){}
    };
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto maintain(int u){
        tr[u].mx=min(tr[ls(u)].mx,tr[rs(u)].mx,comp());
    }
    auto build(int u,int l,int r,vector<point>&ax,const int c){
        auto al=_inf,ar=-_inf,au=_inf,ad=-_inf;
        cir(i,l,r+1){
            al=min(al,ax[i].x);ar=max(ar,ax[i].x);
            au=min(au,ax[i].y);ad=max(ad,ax[i].y);
        }
        tr[u].rng=rectangle(al,ar,au,ad);
        if(l==r) return;
        const auto mid=(l+r)/2;
        nth_element(ax.begin()+l,ax.begin()+mid,ax.begin()+r+1,cmpso[c]);
        build(ls(u),l,mid,ax,c^1);
        build(rs(u),mid+1,r,ax,c^1);
    }
    auto active(int u,int l,int r,point x,auto cost){
        if(!(tr[u].rng&x)) return;
        if(l==r) return tr[u].mx=cost(x.x,x.y),void();
        const auto mid=(l+r)/2;
        active(ls(u),l,mid,x,cost);
        active(rs(u),mid+1,r,x,cost);
        maintain(u);
    }
    auto query(int u,rectangle x){
        if(!(tr[u].rng&x)) return max(-_inf,_inf,comp());
        if(tr[u].rng<x) return tr[u].mx;
        return min(query(ls(u),x),query(rs(u),x),comp());
    }
    int n;
public:
    auto init(vector<point> px){
        build(1,0,n-1,px,0);
    }
    auto active(point u,auto cost){
        active(1,0,n-1,u,cost);
    }
    auto query(rectangle rect){
        return query(1,rect);
    }
    kdtree(int _n):tr(_n<<2),n(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;inf.init();
    int n,q;inf.readargs(n,q);
    const auto sk=inf.iterator();
    vector<point> px;
    cir(i,0,n){
        int x,y;inf.readargs(x,y);
        px.emplace_back(x,y);
    }
    cir(i,0,q){
        int op,x,y;inf.readargs(op,x,y);
        px.emplace_back(x,y);
    }
    inf.fseek(sk);
    kdtree<less<int>> lu(n+q),ld(n+q),ru(n+q),rd(n+q);
    for(auto x:{&lu,&ld,&ru,&rd}) x->init(px);
    cir(i,0,n){
        int x,y;inf.readargs(x,y);
        lu.active(point(x,y),[](auto a,auto b){return -a+-b;});
        ld.active(point(x,y),[](auto a,auto b){return -a+b;});
        ru.active(point(x,y),[](auto a,auto b){return a+-b;});
        rd.active(point(x,y),[](auto a,auto b){return a+b;});
    }
    cir(i,0,q){
        int op,x,y;inf.readargs(op,x,y);
        if(op==1){
            lu.active(point(x,y),[](auto a,auto b){return -a+-b;});
            ld.active(point(x,y),[](auto a,auto b){return -a+b;});
            ru.active(point(x,y),[](auto a,auto b){return a+-b;});
            rd.active(point(x,y),[](auto a,auto b){return a+b;});
        }else{
            cout<<min({
                x+y+lu.query(rectangle(-_inf,x,-_inf,y)),
                x-y+ld.query(rectangle(-_inf,x,y,_inf)),
                -x+y+ru.query(rectangle(x,_inf,-_inf,y)),
                -x-y+rd.query(rectangle(x,_inf,y,_inf))
            })<<'\n';
        }
    }
    return 0;
}
