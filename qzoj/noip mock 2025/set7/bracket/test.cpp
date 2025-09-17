#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream inf("bracket.in");
ofstream ouf("bracket.out");
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
static constexpr auto _infl=(lint)(1e16l);
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
    auto update(int u,int l,int r,int p,lint w){
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
    auto update(int p,lint w){
        update(1,0,n-1,p,w);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n):val(_n<<2,max(
        _infl,-_infl,comp()
    )),n(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;lint a,b;inf>>n>>a>>b;
    string s;inf>>s;
    vector<int> pl(n,-1),pr(n,-1);
    vector<int> pre(n),suf(n);
    [&]{
        auto rpl=0;
        cir(j,0,n){
            if(s[j]=='?'||s[j]=='(') ++rpl;
            else --rpl;
            pre[j]=rpl+n+1;
        }
    }();
    [&]{
        auto rpl=0;
        for(auto j=n-1;~j;--j){
            if(s[j]=='?'||s[j]==')') ++rpl;
            else --rpl;
            suf[j]=rpl+n+1;
        }
    }();
    segment<greater<lint>> sgl(n*2+7);
    cir(i,0,n){
        sgl.update(suf[i],i);
        const auto urp=max(sgl.query(0,(i+1<n?suf[i+1]:n+1)-1)+1,0);
        pl[i]=urp;
    }
    segment<less<lint>> sgr(n*2+7);
    for(auto i=n-1;~i;--i){
        sgr.update(pre[i],i);
        const auto urp=sgr.query(0,(i?pre[i-1]:n+1)-1)-1;
        pr[i]=urp;
    }
    for(auto&x:pr) clog<<x<<' ';
    clog<<'\n';
    segment<greater<lint>> sgk(n*2+7);
    vector<lint> vmn(n+1,-_infl),f(n+1,-_infl);
    vmn[0]=0;f[0]=0;
    cir(i,0,n){
        cir(j,0,i) if(pr[j]<i) vmn[j]=-_infl;
        if(pl[i]<i+1){
            clog<<i<<' '<<pl[i]<<'\n';
            cir(j,pl[i],i+1) if(clog<<"!! "<<i<<' '<<j<<'\n';(i-j)&1) clog<<i<<' '<<j<<'\n',f[i+1]=max(f[i+1],vmn[j]+b);
        }
        f[i+1]+=a*(i+1);
        f[i+1]=max(f[i+1],f[i]);
        vmn[i+1]=f[i+1]-a*(i+1);
    }
    ouf<<*max_element(f.begin(),f.end())<<'\n';
    return 0;
}
