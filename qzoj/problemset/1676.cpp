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
    auto substr(int l,int r){
        return l>r?0:h[r]-(l?h[l-1]:0)*pw[r-l+1];
    }
    hashbase(string _s){init(_s);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;
    while(cin>>s&&s!="."){
        const auto n=(int)(s.size());
        auto ans=n;
        hashbase<uint64_t,251> qwq(s);
        cir(i,1,n) if(!(n%i)){
            auto ok=true;
            for(auto x=0;x<n;x+=i){
                ok&=(qwq.substr(0,i-1)==qwq.substr(x,x+i-1));
            }
            if(ok){
                ans=i;
                break;
            }
        }
        cout<<n/ans<<'\n';
    }
    return 0;
}
