#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
class casereader{
private:
    union datatype{
        int i32;
        lf f128;
        datatype(int x):i32(x){}
        datatype(lf x):f128(x){}
    };
    vector<datatype> data;
    int pos;
    template<typename _Ty>
    auto readarg(){
        _Ty x;cin>>x;data.emplace_back(x);
        return x;
    }
public:
    auto init(){
        const auto n=readarg<int>();
        cir(i,0,n*3) readarg<lf>();
    }
    auto readargs(int&x){
        x=data[pos].i32;++pos;
    }
    auto readargs(lf&x){
        x=data[pos].f128;++pos;
    }
    auto readargs(auto&x,auto&...args){
        readargs(x);readargs(args...);
    }
    casereader():pos(0){}
};
struct point{
    lf x,y;
    point()=default;
    point(auto _x,auto _y):x(_x),y(_y){}
};
// l < r & u < d
class rectangle{
private:
    lf l,r,u,d;
public:
    auto operator&(const rectangle&x){
        return !(l>x.r||r<x.l||u>x.d||d<x.u);
    }
    rectangle()=default;
    rectangle(auto _l,auto _r,auto _u,auto _d):l(_l),r(_r),u(_u),d(_d){}
};
static constexpr auto eps=1e-7l;
class circle{
public:
    point u;lf r;
    int cid;
    auto operator&(const circle&x){
        return norm(complex(u.x-x.u.x,u.y-x.u.y))<(r+x.r)*(r+x.r)+eps;
    }
    operator rectangle() const{
        return rectangle(u.x-r,u.x+r,u.y-r,u.y+r);
    }
    circle()=default;
    circle(auto x,auto y,auto _r,int _id=-1):u(x,y),r(_r),cid(_id){}
};
static const auto cmpso=array{
    function([](const circle&a,const circle&b){return a.u.x<b.u.x;}),
    function([](const circle&a,const circle&b){return a.u.y<b.u.y;})
};
static constexpr auto _inflf=1e12l;
class kdtree{
private:
    struct node{
        rectangle rng;
        unique_ptr<circle> u;
        auto isleaf() const{return (bool)(u);}
        node()=default;
        node(auto _l,auto _r,auto _u,auto _d):rng(_l,_r,_u,_d),u(nullptr){}
    };
    vector<node> tr;
    constexpr auto ls(int x){return x*2;}
    constexpr auto rs(int x){return x*2+1;}
    auto build(int u,int l,int r,int c,vector<circle>&x){
        auto al=_inflf,ar=-_inflf,au=_inflf,ad=-_inflf;
        cir(p,l,r+1){
            const auto&i=x[p];
            al=min(al,i.u.x-i.r);ar=max(ar,i.u.x+i.r);
            au=min(au,i.u.y-i.r);ad=max(ad,i.u.y+i.r);
        }
        tr[u]=node(al,ar,au,ad);
        if(l==r) return tr[u].u=make_unique<circle>(x[l]),void();
        const auto mid=(l+r)/2;
        nth_element(x.begin()+l,x.begin()+mid,x.begin()+r+1,cmpso[c]);
        build(ls(u),l,mid,c^1,x);
        build(rs(u),mid+1,r,c^1,x);
    }
    auto query(int u,const circle&x,vector<int>&ans){
        if(!(tr[u].rng&rectangle(x))) return;
        if(tr[u].isleaf()){
            if(*tr[u].u&x) ans.emplace_back(tr[u].u->cid);
            return;
        }
        query(ls(u),x,ans);
        query(rs(u),x,ans);
    }
public:
    auto init(vector<circle> x){
        build(1,0,(int)(x.size())-1,0,x);
    }
    auto query(const circle x){
        vector<int> ans;
        query(1,x,ans);
        return ans;
    }
    kdtree(int _n):tr(_n<<2){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;inf.init();
    int n;inf.readargs(n);
    vector<circle> x(n);
    random_device rnd;
    const auto arg=uniform_real_distribution<lf>(0,numbers::pi*2)(rnd);
    for(auto cid=-1;auto&i:x){
        lf x,y,r;inf.readargs(x,y,r);
        const auto px=x*cosl(arg)-y*sinl(arg),py=x*sinl(arg)+y*cosl(arg);
        i=circle(px,py,r,++cid);
    }
    kdtree tr(n);
    tr.init(x);
    vector<int> rnk(n);
    iota(rnk.begin(),rnk.end(),0);
    sort(rnk.begin(),rnk.end(),[&](int a,int b){
        return x[a].r==x[b].r?a<b:x[a].r>x[b].r;
    });
    vector<int> ans(n),chk(n);
    iota(ans.begin(),ans.end(),0);
    for(auto&i:rnk) if(!chk[i]){
        chk[i]=true;
        const auto nds=tr.query(x[i]);
        for(auto&x:nds) if(!chk[x]) ans[x]=i,chk[x]=true;
    }
    for(auto&i:ans) cout<<i+1<<' ';
    cout<<'\n';
    return 0;
}
