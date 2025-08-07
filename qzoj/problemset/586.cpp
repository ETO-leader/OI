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
    int n,m;cin>>n>>m;
    string a,b;cin>>a>>b;
    const auto qwq=hashbase<uint64_t,251>(a);
    const auto hb=hashbase<uint64_t,251>(b).substr(0,m-1);
    auto ok=false;
    cir(i,0,n-m+1) if(qwq.substr(i,i+m-1)==hb){
        cout<<i+1<<'\n';ok=true;break;
    }
    if(!ok) cout<<0<<'\n';
    return 0;
}
