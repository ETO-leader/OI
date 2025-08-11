#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename _Ty,const _Ty c>
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
    int n;cin>>n;
    vector<hashbase<uint64_t,251>> qwq;
    vector<string> a(n);
    for(auto&s:a){
        cin>>s;
        qwq.emplace_back(s);
    }
    for(auto&s:a){
        auto ans=0;
        const auto w=hashbase<uint64_t,251>(s).substr(0,(int)(s.size())-1);
        cir(x,0,n){
            cir(i,0,(int)(a[x].size())-(int)(s.size())+1){
                ans+=(qwq[x].substr(i,i+(int)(s.size())-1)==w);
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
