#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using point=complex<int>;
static constexpr auto eps=1e-8l;
constexpr auto same(double a,double b){
    return abs(a-b)<eps;
}
auto abs(point u){
    return sqrt(u.real()*u.real()+u.imag()*u.imag());
}
auto triangle(point u,point x,point y){
    return
        (!same(abs(x-y),abs(x-u)+abs(y-u)))&&
        (!same(abs(x-u),abs(x-y)+abs(u-y)))&&
        (!same(abs(y-u),abs(y-x)+abs(u-x)));
}
auto transform(point u,point x,point y){
    const auto mid=(x+y)/2;
    return u+(mid-u)*2;
}
class storage_type{
private:
    pair<int,int> a,b,c;
public:
    auto operator<(storage_type x) const{
        return make_tuple(a,b,c)<make_tuple(x.a,x.b,x.c);
    }
    storage_type(point u,point v,point w):
        a(u.real(),u.imag()),
        b(v.real(),v.imag()),
        c(w.real(),w.imag()){}
};
auto bfs(point x,point y,point z,int xid,int yid,int zid){
    const auto l_lim=42,r_lim=12;
    queue<tuple<point,point,point>> q;
    map<storage_type,int> opty,dis;
    q.emplace(x,y,z);
    auto success=[&](point u){
        return u.real()>r_lim-1&&u.imag()>r_lim-1;
    };
    auto valid=[&](point u){
        return u.real()>-l_lim&&u.imag()>-l_lim&&u.real()<r_lim*8&&u.imag()<r_lim*8;
    };
    // cerr<<x<<' '<<y<<' '<<z<<'\n';
    opty[{x,y,z}]=-998244353;
    while(!q.empty()){
        const auto[u,v,w]=q.front();
        if(success(u)&&success(v)&&success(w)) break;
        q.pop();
        const auto ut=transform(u,v,w),vt=transform(v,u,w),wt=transform(w,u,v);
        // cerr<<u<<' '<<v<<' '<<w<<" --> "<<ut<<' '<<vt<<' '<<wt<<'\n';
        if(valid(ut)&&(!opty.count({ut,v,w}))){
            opty[{ut,v,w}]=0;
            q.emplace(ut,v,w);
        }
        if(valid(vt)&&(!opty.count({u,vt,w}))){
            opty[{u,vt,w}]=1;
            q.emplace(u,vt,w);
        }
        if(valid(wt)&&(!opty.count({u,v,wt}))){
            opty[{u,v,wt}]=2;
            q.emplace(u,v,wt);
        }
        // cerr<<u<<' '<<v<<' '<<w<<'\n';
    }
    assert(!q.empty());
    vector<tuple<int,int,int>> ops;
    auto[u,v,w]=q.front();
    while(opty[{u,v,w}]>-5){
        const auto opt=opty[{u,v,w}];
        if(opt==0){
            ops.emplace_back(xid,yid,zid);
            u=transform(u,v,w);
        }else if(opt==1){
            ops.emplace_back(yid,zid,xid);
            v=transform(v,u,w);
        }else{
            ops.emplace_back(zid,xid,yid);
            w=transform(w,u,v);
        }
    }
    reverse(ops.begin(),ops.end());
    return make_pair(ops,q.front());
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<point> a(n);
    auto global_ok=true;
    for(auto&u:a){
        double x,y;cin>>x>>y;
        x*=2;y*=2;
        u=point(x,y);
        global_ok&=x>-1&&y>-1;
    }
    if(global_ok){
        cout<<0<<'\n';
    }else{
        auto u=-1,v=-1,w=-1;
        auto succ=false;
        cir(i,0,n) cir(j,i+1,n) cir(k,j+1,n) if(triangle(a[i],a[j],a[k])){
            u=i;v=j;w=k;
            succ=true;
            break;
        }
        if(succ){
            auto[ops,cur]=bfs(a[u],a[v],a[w],u,v,w);
            const auto[x,y,z]=cur;
            cir(i,0,n) if((a[i].real()<0||a[i].imag()<0)&&i!=u&&i!=v&&i!=w){
                if(triangle(a[i],x,y)){
                    ops.emplace_back(i,u,v);
                }else{
                    assert(triangle(a[i],y,z));
                    ops.emplace_back(i,v,w);
                }
            }
            cout<<ops.size()<<'\n';
            for(auto&[a,b,c]:ops) cout<<b+1<<' '<<c+1<<' '<<a+1<<'\n';
        }else{
            cout<<-1<<'\n';
        }
    }
    return 0;
}
