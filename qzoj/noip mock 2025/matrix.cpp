#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("matrix.in");
ofstream ouf("matrix.out");
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
static constexpr auto _infl=(lint)(1e18l);
class rectangle{
public:
    int xl,xr,yl,yr;
    auto operator&(rectangle x) const{
        return (
            (!(xr<x.xl||x.xr<xl))&&
            (!(yr<x.yl||x.yr<yl))
        );
    }
    auto operator<(rectangle x) const{
        return (
            xl>x.xl-1&&
            xr<x.xr+1&&
            yl>x.yl-1&&
            yr<x.yr+1
        );
    }
    rectangle(auto _xl,auto _xr,auto _yl,auto _yr):
        xl(_xl),xr(_xr),yl(_yl),yr(_yr){}
    rectangle()=default;
};
class kdtree{
private:
    struct node{
        rectangle rng;
        lint mn,tag;
        auto upd(auto x){
            mn-=x;
            tag+=x;
        }
        node():mn(_inf),tag(0){}
    };
    vector<node> tr;
    int cnt;
    constexpr auto ls(int u) const{return u*2;}
    constexpr auto rs(int u) const{return u*2+1;}
    template<int type>
    auto build(int u,int l,int r,vector<array<int,3>>&pos){
        tr[u].rng=rectangle(_inf,-_inf,_inf,-_inf);
        cir(i,l,r+1){
            tr[u].rng.xl=min(tr[u].rng.xl,pos[i][0]);
            tr[u].rng.xr=max(tr[u].rng.xr,pos[i][0]);
            tr[u].rng.yl=min(tr[u].rng.yl,pos[i][1]);
            tr[u].rng.yr=max(tr[u].rng.yr,pos[i][1]);
            tr[u].mn=min<lint>(tr[u].mn,pos[i][2]);
        }
        if(l==r) return;
        const auto mid=(l+r)/2;
        sort(pos.begin()+l,pos.begin()+r+1,[&](auto&a,auto&b){
            return a[type]==b[type]?a[type^1]>b[type^1]:a[type]<b[type];
        });
        build<type^1>(ls(u),l,mid,pos);
        build<type^1>(rs(u),mid+1,r,pos);
    }
    auto push_down(int u){
        tr[ls(u)].upd(tr[u].tag);
        tr[rs(u)].upd(tr[u].tag);
        tr[u].tag=0;
    }
    auto maintain(int u){
        tr[u].mn=min(tr[ls(u)].mn,tr[rs(u)].mn);
    }
    auto update(int u,int l,int r,int w,rectangle qry){
        if((!(tr[u].rng&qry))||(tr[u].mn>_inf)) return;
        if(tr[u].mn>w-1&&tr[u].rng<qry) return tr[u].upd(w);
        if(l==r){
            --cnt;
            tr[u].mn=_infl;
            return;
        }
        push_down(u);
        const auto mid=(l+r)/2;
        update(ls(u),l,mid,w,qry);
        update(rs(u),mid+1,r,w,qry);
        maintain(u);
    }
    const int n;
public:
    auto update(rectangle rect,int w){
        update(1,0,n-1,w,rect);
    }
    auto count(){
        return cnt;
    }
    kdtree(vector<array<int,3>> x):n(x.size()),cnt(x.size()),tr(x.size()<<2){
        build<0>(1,0,n-1,x);
    }
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;
    vector<array<int,3>> info(n);
    cir(i,0,n){
        inf>>info[i][1]>>info[i][2];
        info[i][0]=i;
    }
    kdtree kdt(info);
    auto lasans=0;
    cir(i,0,m){
        int xl,yl,xr,yr,c;inf>>xl>>yl>>xr>>yr>>c;
        xl^=lasans;
        xr^=lasans;
        yl^=lasans;
        yr^=lasans;
        c^=lasans;
        --xl;--xr;
        const auto q=rectangle(xl,xr,yl,yr);
        kdt.update(q,c);
        ouf<<(lasans=kdt.count())<<'\n';
    }
    return 0;
}
