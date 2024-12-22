#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using point=complex<lint>;
class casereader{
private:
    union datatype{
        int i32;
        datatype(int x):i32(x){}
    };
    vector<datatype> data;
    int cur;
    template<typename _Ty>
    auto readarg(){
        _Ty x;cin>>x;data.emplace_back(x);
        return x;
    }
public:
    auto init(){
        const auto n=readarg<int>();
        readarg<int>();
        cir(i,0,n*2) readarg<int>();
    }
    auto readargs(int&x){
        x=data[cur].i32;++cur;
    }
    auto readargs(auto&x,auto&...args){
        readargs(x);readargs(args...);
    }
    casereader():cur(0){}
};
static constexpr auto _inf=numeric_limits<int>::max();
static constexpr auto _infl=numeric_limits<lint>::max();
static const auto cmpso=array{
    function([](const point&a,const point&b){return real(a)<real(b);}),
    function([](const point&a,const point&b){return imag(a)<imag(b);})
};
class kdtree{
private:
    struct node{
        int l,r,u,d;
        bool isleaf;
        node()=default;
        node(int _l,int _r,int _u,int _d,bool il):l(_l),r(_r),u(_u),d(_d),isleaf(il){}
    };
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto build(int u,int l,int r,int c,vector<point>&x){
        auto al=_inf,ar=-_inf,au=_inf,ad=-_inf;
        cir(i,l,r+1){
            al=min<int>(al,real(x[i]));ar=max<int>(ar,real(x[i]));
            au=min<int>(au,imag(x[i]));ad=max<int>(ad,imag(x[i]));
        }
        tr[u]=node(al,ar,au,ad,l==r);
        if(l==r) return;
        const auto mid=(l+r)/2;
        nth_element(x.begin()+l,x.begin()+mid,x.begin()+r+1,cmpso[c]);
        build(ls(u),l,mid,c^1,x);
        build(rs(u),mid+1,r,c^1,x);
    }
    auto query(int u,const point q,const int k,priority_queue<lint,vector<lint>,greater<lint>>&cans){
        const auto ul=norm(point(tr[u].l,tr[u].u)-q);
        const auto ur=norm(point(tr[u].r,tr[u].u)-q);
        const auto dl=norm(point(tr[u].l,tr[u].d)-q);
        const auto dr=norm(point(tr[u].r,tr[u].d)-q);
        if(max({ul,ur,dl,dr})<cans.top()+1) return;
        if(tr[u].isleaf) return cans.pop(),cans.push(max({ul,ur,dl,dr})),void();
        query(ls(u),q,k,cans);
        query(rs(u),q,k,cans);
    }
public:
    auto init(vector<point> x){
        build(1,0,(int)(x.size())-1,0,x);
    }
    auto query(const point q,const int k,priority_queue<lint,vector<lint>,greater<lint>>&cans){
        query(1,q,k,cans);
    }
    kdtree(int _n):tr(_n<<2){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;inf.init();
    int n,k;inf.readargs(n,k);k*=2;
    vector<point> x(n);
    for(auto&i:x){
        int x,y;inf.readargs(x,y);
        i=point(x,y);
    }
    kdtree kd(n);kd.init(x);
    priority_queue<lint,vector<lint>,greater<lint>> ans;
    cir(i,0,k) ans.emplace(-_infl);
    cir(i,0,n) kd.query(x[i],k,ans);
    cout<<ans.top()<<'\n';
    return 0;
}
