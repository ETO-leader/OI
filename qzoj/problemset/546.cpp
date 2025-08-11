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
    int n;cin>>n;
    string s;cin>>s;
    vector<int> mw(n+1);
    iota(mw.begin(),mw.end(),0);
    cir(i,2,n+1) if(mw[i]==i){
        for(auto j=i;j<n+1;j+=i) mw[j]=min(mw[j],i);
    }
    hashbase<uint64_t,251> qwq(s);
    int q;cin>>q;
    cir(i,0,q){
        int l,r;cin>>l>>r;--l;--r;
        auto w=r-l+1;
        auto prd=1;
        while(w>1){
            const auto v=mw[w];
            auto cnt=0;
            while(mw[w]==v) ++cnt,w/=v;
            auto pw=1;
            cir(i,0,cnt){
                pw*=v;
                if(qwq.substr(l,r-(r-l+1)/pw)==qwq.substr(l+(r-l+1)/pw,r)) prd*=v;
            }
        }
        cout<<(r-l+1)/prd<<'\n';
    }
    return 0;
}
