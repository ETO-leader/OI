#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(lint)(1e18+7);
class blocks{
private:
    struct node{
        int l,r;lint wx,sumb,fx,gx;
    };
    vector<node> ns;
    vector<int> bid;
    vector<lint> ai,bi,ci;
    auto build(int n){
        const auto sqr=(int)(ceil(sqrt(n)));
        for(auto i=0;i<n;i+=sqr){
            ns.push_back({i,min(i+sqr-1,n-1)});
        }
        for(auto c=0;auto&[l,r,na,nb,nc,nd]:ns){
            cir(i,l,r+1) bid[i]=c;
            ++c;
        }
    }
    auto update(int l,int r,node&u){
        auto fx=0ll,wx=0ll,gx=_inf,prb=0ll;
        cir(i,l,r+1){
            prb+=bi[i];
            wx+=min(fx+ai[i],bi[i]);
            fx=min(ci[i],max<lint>(fx+ai[i]-bi[i],0));
            gx=min(gx,(prb-wx)+(ci[i]-fx));
        }
        u.wx=wx;u.sumb=prb;u.fx=fx;u.gx=gx;
    }
public:
    auto update(int p,lint a,lint b,lint c){
        ai[p]=a;bi[p]=b;ci[p]=c;
        auto&pu=ns[bid[p]];
        update(pu.l,pu.r,pu);
    }
    auto query(){
        auto nfl=0ll,res=0ll;
        for(auto&[l,r,wx,sumb,fx,gx]:ns){
            nfl=min(nfl,gx);
            const auto nx=min(nfl,sumb-wx);
            res+=nx+wx;nfl+=fx-nx;
        }
        return res;
    }
    blocks(int _n):ai(_n),bi(_n),ci(_n),bid(_n){
        build(_n);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;blocks blc(n);
    vector<lint> a(n),b(n),c(n-1);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    for(auto&i:c) cin>>i;
    c.push_back(_inf);
    cir(i,0,n) blc.update(i,a[i],b[i],c[i]);
    cir(i,0,q){
        lint p,ai,bi,ci;cin>>p>>ai>>bi>>ci;
        blc.update(p-1,ai,bi,ci);
        cout<<blc.query()<<'\n';
    }
    return 0;
}
