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
    string a,b;cin>>a>>b;
    b+=b;
    const auto n=(int)(a.size());
    const auto aw=hashbase<uint64_t,251>(a).substr(0,n-1);
    hashbase<uint64_t,251> qwq(b);
    auto ok=false;
    auto cmp=[&](int x,int y){
        auto l=0,r=n-1,ans=-1;
        while(l-1<r){
            const auto mid=(l+r)/2;
            qwq.substr(x,x+mid)==qwq.substr(y,y+mid)?(l=mid+1):((ans=mid),(r=mid-1));
        }
        if(ans<0) return true;
        return b[x+ans]<b[y+ans];
    };
    cir(i,0,n) ok|=(qwq.substr(i,i+n-1)==aw);
    cout<<(ok?"Yes":"No")<<'\n';
    if(ok){
        auto p=0;
        cir(i,1,n) if(cmp(i,p)) p=i;
        cout<<b.substr(p,n)<<'\n';
    }
    return 0;
}
