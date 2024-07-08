#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=double;
using point=complex<lf>;
using vector_t=complex<lf>;
static constexpr auto eps=1e-8;
static constexpr auto _inf=1e12;
static constexpr auto nanlf=nan("");
static constexpr auto invaildp=point(nanlf,nanlf);
auto cross(vector_t a,vector_t b){
    return (conj(a)*b).imag();
}
constexpr auto invaild(const point p){
    return isnan(p.real())||isnan(p.imag());
}
constexpr auto iszero(lf x){
    return abs(x)<eps;
}
template<typename _Ty>
constexpr auto same(_Ty a,_Ty b){
    return iszero(abs(a-b));
}
constexpr auto sign(lf x){
    return (x<0?-1:1)*(!iszero(x));
}
class line{
private:
    point u;vector_t v;
    friend class circle;
public:
    auto norm() const{return v*1i;}
    auto dist(point p) const{
        return abs(cross(v,p-u))/abs(v);
    }
    line(point a,point b):u(a),v((b-a)/abs(b-a)){}
};
class segment{
private:
    point u;vector_t v;
public:
    auto norm() const{return v*1i;}
    auto inrange(point p){
        return same(abs(u-p)+abs(u+v-p),abs(v));
    }
    segment(point a,point b):u(a),v(b-a){}
};
class circle{
private:
    point u;lf r;
public:
    auto inter(const line l) const{
        const auto dis=l.dist(u);
        if(dis>r+eps) return pair(invaildp,invaildp);
        const auto ldis=sqrt(r*r-dis*dis+eps);
        const auto carg=dis/r,sarg=ldis/r;
        const auto veca=l.norm()*vector_t(carg,sarg)*r;
        const auto vecb=l.norm()*vector_t(carg,-sarg)*r;
        const auto vecc=-l.norm()*vector_t(carg,sarg)*r;
        const auto vecd=-l.norm()*vector_t(carg,-sarg)*r;
        if(iszero(l.dist(u+veca))) return pair(u+veca,u+vecb);
        return pair(u+vecc,u+vecd);
    }
    auto inter(const circle c) const{
        if(abs(u-c.u)>r+c.r+eps) return pair(invaildp,invaildp);
        const auto lndir=line(u,c.u).norm();
        const auto lnpos=(u*c.r+c.u*r)/(r+c.r);
        return inter(line(lnpos,lnpos+lndir));
    }
    auto inside(point p){return abs(p-u)<r-eps;}
    auto center() const{return u;}
    circle(point _u,lf _r):u(_u),r(_r){}
    circle()=default;
};
class graph{
private:
    struct edge{int v;lf w;};
    struct heapnode{int u;lf w;};
    class nodecmp{
    public:
        auto operator()(const heapnode&a,heapnode&b) const{
            return a.w>b.w;
        }
    };
    vector<vector<edge>> gr;
    auto dijkstra(int ux,int vx){
        priority_queue<heapnode,vector<heapnode>,nodecmp> pq;
        vector<lf> dis(gr.size(),_inf);vector<int> vis(gr.size());
        dis[ux]=0.0;pq.push({ux,0.0});
        while(!pq.empty()){
            const auto[u,w]=pq.top();pq.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(auto&[v,wi]:gr[u]){
                if(vis[v]||w+wi>dis[v]) continue;
                dis[v]=w+wi;
                pq.push({v,dis[v]});
            }
        }
        return vis[vx]?dis[vx]:-1.0;
    }
public:
    auto insert(int u,int v,lf w){
        gr[u].push_back({v,w});
        gr[v].push_back({u,w});
    }
    auto calc(int u,int v){
        return dijkstra(u,v);
    }
    graph(int _n):gr(_n){}
};
auto vaild(point a,point b,vector<circle>&cls){
    const auto l=line(a,b);
    vector<pair<point,int>> fds;
    for(auto id=-1;auto&i:cls){
        ++id;
        const auto[pa,pb]=i.inter(l);
        if(invaild(pa)||invaild(pb)) continue;
        fds.push_back({pa,id});
        fds.push_back({pb,id});
    }
    sort(fds.begin(),fds.end(),[&](auto&a,auto&b){
        return same(a.first.real(),b.first.real())?
            a.first.imag()<b.first.imag():
            a.first.real()<b.first.real();
    });
    unordered_set<int> ids;
    point las=point(_inf,_inf);
    for(auto&[u,id]:fds){
        if(ids.empty()&&segment(a,b).inrange(u)&&(!same(u,las)))
            return false;
        if(ids.count(id)) ids.erase(id);
        else ids.insert(id);
        las=u;
    }
    return true;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,d,s,t;cin>>n>>d>>s>>t;
    vector<circle> cs(n);
    for(auto&i:cs){
        lf x,y;cin>>x>>y;
        i=circle(point(x,y),d);
    }
    vector<point> itrs;
    cir(i,0,n) cir(j,i+1,n){
        const auto[ia,ib]=cs[i].inter(cs[j]);
        for(auto x:{ia,ib}) if(!invaild(x)) itrs.push_back(x);
    }
    [&](vector<point> px){
        itrs.clear();
        for(auto&i:cs) itrs.push_back(i.center());
        for(auto&x:px){
            auto ok=true;
            for(auto&c:cs) ok&=(!c.inside(x));
            if(ok) itrs.push_back(x);
        }
    }(itrs);
    const auto nds=(int)(itrs.size());
    graph gr(nds);
    cir(i,0,nds) cir(j,i+1,nds){
        if(vaild(itrs[i],itrs[j],cs)){
            gr.insert(i,j,abs(itrs[i]-itrs[j]));
        }
    }
    const auto ans=gr.calc(s-1,t-1);
    if(ans<0) cout<<-1<<'\n';
    else cout<<fixed<<setprecision(2)<<ans<<'\n';
    return 0;
}
