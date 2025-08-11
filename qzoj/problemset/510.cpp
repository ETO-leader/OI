#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<class _Ty,const _Ty c>
class hashbase{
private:
    vector<_Ty> h,pw;
    auto init(string s){
        auto w=0ll;
        for(auto&i:s) h.emplace_back((w*=c)+=i);
        pw.resize(s.size()+7);
        auto x=(_Ty)(1);
        for(auto&i:pw) i=x,x*=c;
    }
public:
    constexpr auto substr(int l,int r) const{
        return l>r?0:h[r]-(l?h[l-1]:0)*pw[r-l+1];
    }
    hashbase(string _s){init(_s);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        string a,b;cin>>a>>b;
        const auto ah=hashbase<uint64_t,251>(a).substr(0,(int)(a.size())-1);
        auto ans=0;
        const auto qwq=hashbase<uint64_t,251>(b);
        cir(i,0,(int)(b.size())-(int)(a.size())+1) ans+=(qwq.substr(i,i+(int)(a.size())-1)==ah);
        cout<<ans<<'\n';
    }();
    return 0;
}
