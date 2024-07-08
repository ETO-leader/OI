#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
struct poly{
private:
    vector<bool> cks;
    vector<lint> w;lint cl;
    template<typename _Ty>
    static constexpr auto lowbit(_Ty x){
        return x&(-x);
    }
    auto build(int x,int v){
        for(;x;x-=lowbit(x)){
            cks[__builtin_ctz(x)]=true;
            w[__builtin_ctz(x)]=x*(lint)(x^v)%MOD;
        }
    }
    auto fwt(const poly&x) const{
        vector<lint> wa(22),wb(22);
        wa[0]=cl;wb[0]=x.cl;
        cir(i,1,22){
            (wa[i]+=wa[i-1]+(w[i-1]<<(i-1)))%=MOD;
            (wb[i]+=wb[i-1]+(x.w[i-1]<<(i-1)))%=MOD;
        }
        poly res;auto spr=0ll;
        for(auto i=21;~i;--i){
            res.w[i]=(wa[i]*x.w[i]+wb[i]*w[i]+spr)%MOD;
            res.cks[i]=cks[i]^x.cks[i];
            (spr+=(w[i]<<i)%MOD*x.w[i])%=MOD;
        }
        res.cl=(spr+cl*x.cl)%MOD;
        return res;
    }
public:
    auto operator*(const poly&a) const{
        return fwt(a);
    }
    auto query(int x){
        for(auto i=21;~i;--i) if(((x>>i)&1)!=cks[i])
            return w[i];
        return cl;
    }
    poly():cks(22),w(22),cl(0){}
    poly(int x,int v):cks(22),w(22),cl(0){
        build(x,v);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;
    vector<poly> ans(n);
    cir(i,0,n){
        int x,v;cin>>x>>v;
        const auto ins=poly(x,v);
        if(i) ans[i]=ans[i-1]*ins;
        else ans[i]=ins;
    }
    cir(i,0,q){
        int c,d;cin>>c>>d;
        cout<<ans[c-1].query(d)<<'\n';
    }
    return 0;
}
