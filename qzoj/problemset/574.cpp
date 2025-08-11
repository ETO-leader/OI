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
    string s;cin>>s;
    const auto n=(int)(s.size());
    const auto qwq=hashbase<uint64_t,251>(s);
    auto check=[&](int mid){
        unordered_set<uint64_t> res;
        cir(i,0,n-mid+1){
            if(res.count(qwq.substr(i,i+mid-1))) return true;
            res.emplace(qwq.substr(i,i+mid-1));
        }
        return false;
    };
    auto l=1,r=n,ans=-1;
    while(l-1<r){
        const auto mid=(l+r)/2;
        check(mid)?((l=mid+1),(ans=mid)):(r=mid-1);
    }
    unordered_set<uint64_t> x;
    cir(i,0,n-ans+1){
        if(x.count(qwq.substr(i,i+ans-1))){
            cout<<s.substr(i,ans)<<'\n';
            break;
        }
        x.emplace(qwq.substr(i,i+ans-1));
    }
    return 0;
}
