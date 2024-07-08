#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using point=complex<long>;
using pointf=complex<double>;
template<typename point_t>
constexpr auto x(const point_t&p){return real(p);}
template<typename point_t>
constexpr auto y(const point_t&p){return imag(p);}
class segment{
private:
    struct node{
        node*ls,*rs;
        int cnt;
        node():ls(nullptr),rs(nullptr),cnt(0){}
        ~node(){
            if(ls) delete ls;
            if(rs) delete rs;
        }
    };
    node*root;
    static constexpr auto eps=1e-2;
    template<const int val>
    auto update(node*&u,double l,double r,double ql,double qr){
        if(!u) u=new node();
        if(ql<l+eps&&r-eps<qr) return u->cnt+=val,void(); 
        const auto mid=(l+r)/2;
        if(ql<mid) update<val>(u->ls,l,mid,ql,qr);
        if(mid<qr) update<val>(u->rs,mid,r,ql,qr);
    }
    auto count(node*u,double l,double r,double p){
        if(!u) return false;
        if(r-l<eps) return (bool)(u->cnt);
        if(u->cnt) return true;
        const auto mid=(l+r)/2;
        return p<mid?count(u->ls,l,mid,p):
            count(u->rs,mid,r,p);
    }
    static constexpr auto mn=-2e8,mx=2e8;
public:
    auto insert(double l,double r){
        update<1>(root,mn,mx,l,r);
    }
    auto extrace(double l,double r){
        update<-1>(root,mn,mx,l,r);
    }
    auto count(double p){
        return count(root,mn,mx,p);
    }
    segment():root(nullptr){}
    ~segment(){if(root) delete root;}
};
// y=kx+b
struct line{
    long double k,b;
    constexpr auto getmrg(const line&l) const{
        //k₁x+b₁=k₂x+b₂
        //(k₁-k₂)x=b₂-b₁
        //x=(b₂-b₁)/(k₁-k₂)
        const auto mx=(long double)(l.b-b)/(k-l.k);
        assert(abs(k*mx+b-(l.k*mx+l.b))<1e-9);
        const auto my=k*mx+b;
        return pointf(mx,my);
    }
    line(long _k,long _b):k(_k),b(_b){}
    line(point s,point t){
        k=(double)(y(t)-y(s))/(x(t)-x(s));
        b=y(s)-k*x(s);
    }
};
auto getpoint(vector<pair<int,int>> p,int sx,int ex){
    vector<pointf> mgs;
    set<pair<int,int>,greater<pair<int,int>>> lc;
    vector<line> linei;
    for(auto&[xi,yi]:p) linei.push_back(line(point(sx,xi),point(ex,yi)));
    for(auto c=-1;auto[xi,yi]:p){
        ++c;
        for(auto&[ry,id]:lc){
            if(ry<yi+1) break;
            mgs.push_back(linei[c].getmrg(linei[id]));
        }
        lc.insert({yi,c});
    }
    return mgs;
}
auto fndcircle(int u,vector<bool>&vis,vector<vector<int>>&gr){
    if(vis[u]) return;
    vis[u]=true;
    for(auto&i:gr[u]) fndcircle(i,vis,gr);
}
auto checkcnt(vector<int> rst){
    vector<int> loc(rst.size());
    iota(loc.begin(),loc.end(),0);
    sort(loc.begin(),loc.end(),[&](int u,int v){
        return rst[u]<rst[v];
    });
    vector<vector<int>> gr(rst.size());
    vector<bool> vis(rst.size());
    auto cnt=0;
    cir(i,0,(int)(rst.size())){
        gr[i].push_back(loc[i]);
    }
    cir(i,0,(int)(rst.size())) if(!vis[i]){
        fndcircle(i,vis,gr);++cnt;
    }
    return cnt;
}
struct qry{
    double x,lfy,rgy;int type;
    qry(double _x,double _lfy,double _rgy,int _type):
        x(_x),lfy(_lfy),rgy(_rgy),type(_type){}
};
auto scan(const vector<pointf> p,const vector<pair<point,int>> q){
    segment sg;
    vector<qry> qs;
    for(auto&i:p) qs.push_back(qry(x(i),y(i),y(i),-1));
    for(auto&[i,r]:q){
        qs.push_back(qry(x(i)-r,y(i)-r,y(i)+r,0));
        qs.push_back(qry(x(i)+r+1e-2,y(i)-r,y(i)+r,1));
    }
    sort(qs.begin(),qs.end(),[](auto&a,auto&b){
        return a.x==b.x?a.type>b.type:a.x<b.x;
    });
    auto cnt=0;
    for(auto&[x,lfy,rgy,type]:qs){
        if(type==-1){
            cnt+=sg.count(lfy);
        }else if(!type){
            sg.insert(lfy,rgy);
        }else{
            sg.extrace(lfy,rgy);
        }
    }
    return cnt;
}
template<typename point_t>
auto change(vector<point_t>&ps){
    for(auto&i:ps) i=pointf(x(i)+y(i),x(i)-y(i));
}
auto change(vector<pair<point,int>>&ps){
    for(auto&[i,r]:ps) i=pointf(x(i)+y(i),x(i)-y(i));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,a,b,c,sx,ex;cin>>n>>a>>b>>c>>sx>>ex;
    vector<pair<int,int>> sy(n);
    for(auto&[a,b]:sy) cin>>a;
    for(auto&[a,b]:sy) cin>>b;
    auto mrgp=getpoint(sy,sx,ex);
    int k;cin>>k;
    vector<pair<point,int>> fndr(k);
    for(auto&i:fndr) i=[](){
        int a,b,r;cin>>a>>b>>r;
        return pair(point(a,b),r);
    }();
    change(mrgp);change(fndr);
    const auto fndchg=checkcnt([&](){
        vector<int> res;
        for(auto&[a,b]:sy) res.push_back(b);
        return res;
    }());
    const auto bscad=scan(mrgp,fndr)*c;
    const auto csta=(int)(mrgp.size())*a+bscad;
    const auto cstb=(n-fndchg)*a+(int)(mrgp.size()+fndchg-n)*b+bscad;
    cout<<min(csta,cstb)<<' '<<max(csta,cstb)<<'\n';
    return 0;
}
