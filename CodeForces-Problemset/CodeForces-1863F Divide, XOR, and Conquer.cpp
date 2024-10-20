#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto oktag=(1ull<<63);
constexpr auto highbit(auto x){
    if(x==oktag) return x;
    return (decltype(x))(1)<<(sizeof(x)*8-1-countl_zero(x));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<uint64_t> a(n);
        for(auto&i:a) cin>>i;
        auto pxor=a;
        cir(i,1,n) pxor[i]^=pxor[i-1];
        vector<uint64_t> lf(n),rg(n);
        auto rgxor=[&](int l,int r){
            const auto res=pxor[r]^(l?pxor[l-1]:0);
            return res?res:oktag;
        };
        lf[0]=rg[n-1]=highbit(rgxor(0,n-1));
        auto ans=string(n,'0');
        for(auto len=n;len;--len) cir(l,0,n-len+1){
            const auto r=l+len-1;
            const auto ok=(bool)(((rgxor(l,r)|oktag)&lf[l])|((rgxor(l,r)|oktag)&rg[r]));
            if(ok) lf[l]|=highbit(rgxor(l,r)),rg[r]|=highbit(rgxor(l,r));
            ans[l]='0'+ok;
        }
        println("{}",ans);
    }();
    return 0;
}
