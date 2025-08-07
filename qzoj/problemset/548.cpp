#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename _Ty,const _Ty c>
class hashbase{
private:
    vector<_Ty> a,ra,pw;
    auto init(string s){
        auto h=(uint64_t)(0);
        for(auto&i:s) a.emplace_back((h*=c)+=i);
        ra.emplace_back(h=0);
        reverse(s.begin(),s.end());
        for(auto&i:s) ra.emplace_back((h*=c)+=i);
        reverse(ra.begin(),ra.end());
        pw.resize(s.size()+7,1);
        cir(i,1,(int)(s.size())+7) pw[i]=pw[i-1]*c;
    }
public:
    auto substr(int l,int r){
        return a[r]-(l?a[l-1]:0)*pw[r-l+1];
    }
    auto rsubstr(int l,int r){
        return ra[l]-ra[r+1]*pw[r-l+1];
    }
    hashbase(string s){init(s);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    string s;cin>>s;
    hashbase<uint64_t,251> qwq(s);
    for(auto&x:s) x=(x=='1'?'0':'1');
    hashbase<uint64_t,251> rqwq(s);
    auto ans=0;
    cir(i,0,n-1){
        const auto len=min(i,n-i-2)+1;
        auto l=0,r=len,uans=0;
        while(l-1<r){
            const auto mid=(l+r)/2;
            qwq.substr(i-mid+1,i)==rqwq.rsubstr(i+1,i+mid)?((l=mid+1),(uans=mid)):(r=mid-1);
        }
        ans+=uans;
    }
    cout<<ans<<'\n';
    return 0;
}
