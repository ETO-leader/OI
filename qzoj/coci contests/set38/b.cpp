#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto eps=1e-15l;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int k;cin>>k;vector<int> z(k);
    for(auto&i:z) cin>>i;
    string s;cin>>s;
    auto calc=[&](auto __self,int p){
        assert(s[p]=='(');
        ++p;
        if(s[p]=='?') return make_pair((long double)(z[0]),p+1);
        auto op='.';
        vector<long double> uw;
        --p;
        while(s[p]!=')'){
            ++p;
            const auto[w,r]=__self(__self,p);
            p=r+1;
            if(s[p]!=')') op=s[p];
            uw.emplace_back(w);
        }
        if(op=='.') return make_pair(min<long double>(z[0],uw[0]),p);
        if(op=='+') return make_pair(min<long double>(accumulate(uw.begin(),uw.end(),0.0l),z[uw.size()-1]),p);
        auto l=0.0l,r=(long double)(z[uw.size()-1]);
        cir(i,0,80){
            const auto mid=(l+r)/2;
            auto sum=0.0l;
            for(auto&x:uw) sum+=min(x,mid);
            sum<z[uw.size()-1]+eps?l=mid:r=mid;
        }
        auto w=(l+r)/2;
        auto ans=1.0l;
        for(auto&x:uw) ans*=min(x,w);
        return make_pair(ans,p);
    };
    cout<<fixed<<setprecision(15)<<calc(calc,0).first<<'\n';
    return 0;
}
