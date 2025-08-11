#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto c=251ull;
class segment{
private:
    vector<uint64_t> val,pw;
    constexpr auto ls(int u) const{return u*2;}
    constexpr auto rs(int u) const{return u*2+1;}
    auto maintain(int u){
        val[u]=val[ls(u)]+val[rs(u)]*pw[ls(u)];
        pw[u]=pw[ls(u)]*pw[rs(u)];
    }
    auto build(int u,int l,int r){
        if(l==r) return pw[u]=c;
        const auto mid=(l+r)/2;
        return pw[u]=build(ls(u),l,mid)*build(rs(u),mid+1,r);
    }
    auto update(int u,int l,int r,int p,uint64_t w){
        if(l==r) return val[u]+=w,void();
        const auto mid=(l+r)/2;
        (p-1<mid)?update(ls(u),l,mid,p,w):update(rs(u),mid+1,r,p,w);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(r<ql||qr<l) return make_pair((uint64_t)(0),(uint64_t)(1));
        if(ql-1<l&&r-1<qr) return make_pair(val[u],pw[u]);
        const auto mid=(l+r)/2;
        const auto[ul,pl]=query(ls(u),l,mid,ql,qr);
        const auto[ur,pr]=query(rs(u),mid+1,r,ql,qr);
        return make_pair(ul+ur*pl,pl*pr);
    }
    const int n;
public:
    auto update(int p,uint64_t w){
        update(1,0,n-1,p,w);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r).first;
    }
    segment(int _n):val(_n<<2),pw(_n<<2),n(_n){build(1,0,n-1);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> a(n);
    for(auto&i:a) cin>>i,--i;
    auto ok=false;
    segment sl(n),sr(n);
    cir(i,0,n){
        const auto len=min(a[i],n-1-a[i]);
        if(len){
            const auto lw=sl.query(a[i]-len,a[i]-1);
            const auto rw=sr.query((n-a[i]-1)-len,(n-a[i]-1)-1);
            ok|=(lw!=rw);
        }
        sl.update(a[i],1);
        sr.update(n-a[i]-1,1);
    }
    cout<<(ok?"YES":"NO")<<'\n';
    return 0;
}
