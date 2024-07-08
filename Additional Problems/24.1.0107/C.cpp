#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
using db=long double;
static constexpr db eps=1e-15L;
struct vector_t{
    db x,y;int id;
    auto operator+(const vector_t&a) const{
        return vector_t(x+a.x,y+a.y);
    }
    auto operator-(const vector_t&a) const{
        return vector_t(x-a.x,y-a.y);
    }
    auto operator*(const int a) const{
        return vector_t(x*a,y*a);
    }
    auto operator&(const vector_t&a) const{
        return x*a.x+y*a.y;
    }
    auto dist() const{
        return sqrtl(x*x+y*y);
    }
    vector_t(db _x=0,db _y=0):
        x(_x),y(_y),id(0){}
};
using point=vector_t;
struct seg{
    point l,r;int id;
    seg(point _l,point _r):l(_l),r(_r),id(0){}
};
istream&operator>>(istream&is,point&x){
    return is>>x.x>>x.y;
}
auto cp(point x){
    complex<db> res(x.x,x.y);
    return res;
}
auto cross(complex<db> a,complex<db> b){
    return imag(conj(a)*b);
}
auto ckmrg(seg a,seg b){
    auto x=cp(a.l),y=cp(a.r),u=cp(b.l),v=cp(b.r);
    return cross(u-x,y-x)*cross(v-x,y-x)<=0;
}
struct edge{int v;db w;};
vector<vector<edge>> G;
struct heapnode{
    int u;db w;
    auto operator<(const heapnode&x) const{
        return w>x.w;
    }
};
auto dijkstra(int ux,int vx){
    priority_queue<heapnode> pq;
    vector<db> f(G.size(),1e18L);
    f[ux]=0;pq.push({ux,0});
    vector<bool> vis(G.size());
    while(!pq.empty()){
        auto u=pq.top();pq.pop();
        if(vis[u.u]) continue;
        vis[u.u]=true;
        for(auto&i:G[u.u]) if(!vis[i.v]){
            if(u.w+i.w>f[i.v]) continue;
            f[i.v]=u.w+i.w;
            pq.push({i.v,u.w+i.w});
        }
    }
    return f[vx];
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    mt19937 seedx(time(nullptr));
    uniform_real_distribution<db> rnd(0,acos(-1)*2);
    while(T--){
        point p1,p2;cin>>p1>>p2;p1.id=0;p2.id=1;
        vector<point> ps{p1,p2};
        vector<seg> sgs;
        sgs.push_back({p1,p1});sgs.back().id=0;
        sgs.push_back({p2,p2});sgs.back().id=1;
        int cid=1,xid=1;
        cir(i,0,3){
            point a,b,c;cin>>a>>b>>c;
            a.id=++cid;b.id=++cid;c.id=++cid;
            sgs.push_back({a,b});sgs.back().id=++xid;
            sgs.push_back({a,c});sgs.back().id=xid;
            sgs.push_back({b,c});sgs.back().id=xid;
            ps.push_back(a);
            ps.push_back(b);
            ps.push_back(c);
            auto rndp=[&](point p){
                cir(i,0,5){
                    auto alg=rnd(seedx);
                    auto np=p+vector_t(cos(alg)*1e-8L,sin(alg)*1e-8L);
                    ps.push_back(np);np.id=++cid;
                    sgs.push_back({np,np});
                    sgs.back().id=++xid;
                }
            };
            rndp(a);rndp(b);rndp(c);
        }
        const auto n=ps.size();G.clear();G.resize(n);
        cir(i,0,sgs.size()) cir(j,i+1,sgs.size()){
            cir(x,0,2) cir(y,0,2){
                auto u=x?sgs[i].r:sgs[i].l;
                auto v=y?sgs[j].r:sgs[j].l;
                auto ok=true;
                cir(k,2,sgs.size()) if(i!=k&&j!=k){
                    if((sgs[k].id!=sgs[i].id&&sgs[k].id!=sgs[j].id)||(!(
                        sgs[k].l.id==u.id||sgs[k].l.id==v.id||
                        sgs[k].r.id==u.id||sgs[k].r.id==v.id
                    ))){
                        ok&=(!(ckmrg(sgs[k],seg(u,v))&&ckmrg(seg(u,v),sgs[k])));
                    }
                }
                if(!ok) continue;
                G[u.id].push_back({v.id,(u-v).dist()});
                G[v.id].push_back({u.id,(u-v).dist()});
            }
        }
        cout<<fixed<<setprecision(5)<<dijkstra(0,1)<<'\n';
    }
    return 0;
}
