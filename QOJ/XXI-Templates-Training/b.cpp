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
        for(auto x=(_Ty)(1);auto&i:pw) i=x,x*=c;
    }
public:
    auto substr(int l,int r){
        return l>r?0:h[r]-(l?h[l-1]:0)*pw[r-l+1];
    }
    hashbase(string _s){init(_s);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    const auto n=(int)(s.size());
    hashbase<uint64_t,251> qwq(s);
    cir(i,0,n){
        auto ans=0;
        if(i){
            auto l=0,r=n-i;
            while(l-1<r){
                const auto mid=midpoint(l,r);
                qwq.substr(0,mid-1)==qwq.substr(i,i+mid-1)?((l=mid+1),(ans=mid)):(r=mid-1);
            }
        }
        cout<<ans<<' ';
    }
    cout<<'\n';
    return 0;
}
