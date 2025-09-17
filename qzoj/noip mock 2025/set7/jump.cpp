#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream inf("jump.in");
ofstream ouf("jump.out");
static constexpr auto _inf=(int)(1e9+7);
template<class comp>
class segment{
private:
    vector<int> val;
    static const auto initval=max(
        _inf,-_inf,comp()
    );
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto maintain(int u){
        val[u]=min(val[ls(u)],val[rs(u)],comp());
    }
    auto update(int u,int l,int r,int p,int w){
        if(l==r) return val[u]=w,void();
        const auto mid=(l+r)/2;
        p-1<mid?update(ls(u),l,mid,p,w):update(rs(u),mid+1,r,p,w);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(qr<l||r<ql) return initval;
        if(ql-1<l&&r-1<qr) return val[u];
        const auto mid=(l+r)/2;
        return min(query(ls(u),l,mid,ql,qr),query(rs(u),mid+1,r,ql,qr),comp());
    }
    const int n;
public:
    auto update(int p,int w){
        update(1,0,n-1,p,w);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n):val(_n<<2,max(
        _inf,-_inf,comp()
    )),n(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,q,t;inf>>n>>q>>t;
    vector<int> v(n),a(n),b(n);
    for(auto&i:v) inf>>i;
    v.emplace_back(n+1);
    for(auto&i:a) inf>>i;
    for(auto&i:b) inf>>i;
    if(t<2){
        vector<vector<pair<int,int>>> vx(n+1);
        cir(i,0,n){
            vx[i].emplace_back(i+1,a[i]);
            cir(j,i,n+1) if(v[j]>v[i]){
                vx[i].emplace_back(j,b[i]);
                break;
            }
        }
        cir(i,0,q){
            int u,v;inf>>u>>v;--u;--v;
            vector<int> f(n+1,_inf);
            f[u]=0;
            cir(j,u,v){
                for(auto&[x,w]:vx[j]) f[x]=min(f[x],max(f[j],w));
            }
            ouf<<f[v]<<'\n';
        }
    }else{
        segment<greater<int>> sg(n);
        cir(i,0,n) sg.update(i,a[i]);
        vector<int> f(n+1);
        for(auto i=n-1;~i;--i){
            f[i]=min(max(f[i+1],a[i]),b[i]);
        }
        cir(i,0,q){
            int u,v;inf>>u>>v;--u;--v;
            if(u==v){
                ouf<<0<<'\n';
            }else if(v==n){
                ouf<<min(sg.query(u,v-1),f[u])<<'\n';
            }else{
                ouf<<sg.query(u,v-1)<<'\n';
            }
        }
    }
    return 0;
}

