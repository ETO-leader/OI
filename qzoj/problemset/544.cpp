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
    string s;
    while(cin>>s) [&]{
        hashbase<uint64_t,251> h(s);
        cir(l,1,(int)(s.size())+1){
            if(h.substr(0,l-1)==h.substr((int)(s.size())-l,(int)(s.size())-1)) cout<<l<<' ';
        }
        cout<<'\n';
    }();
    return 0;
}
