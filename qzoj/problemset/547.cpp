#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename _Ty,const _Ty c>
class hashbase{
private:
    vector<_Ty> h,rh,pw;
    auto init(auto x){
        auto w=0ll;
        for(auto&i:x) h.emplace_back((w*=c)+=i);
        w=0;
        reverse(x.begin(),x.end());
        for(auto&i:x) rh.emplace_back((w*=c)+=i);
        reverse(rh.begin(),rh.end());
        rh.emplace_back(0);
        pw.resize(x.size()+7,1);
        cir(i,1,(int)(pw.size())) pw[i]=pw[i-1]*c;
    }
public:
    auto substr(int l,int r) const{
        return h[r]-(l?h[l-1]:0)*pw[r-l+1];
    }
    auto rsubstr(int l,int r) const{
        return rh[l]-rh[r+1]*pw[r-l+1];
    }
    hashbase(auto x){init(x);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    hashbase<uint64_t,512251> qwq(a);
    map<int,vector<int>,greater<>> chk;
    cir(k,1,n+1){
        unordered_set<uint64_t> apr;
        for(auto i=0;i+k-1<n;i+=k){
            const auto x=qwq.substr(i,i+k-1);
            const auto y=qwq.rsubstr(i,i+k-1);
            if((!apr.count(x))&&(!apr.count(y))) apr.emplace(x);
        }
        chk[apr.size()].emplace_back(k);
    }
    cout<<chk.begin()->first<<' '<<chk.begin()->second.size()<<'\n';
    for(auto&x:chk.begin()->second) cout<<x<<' ';
    cout<<'\n';
    return 0;
}
