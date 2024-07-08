#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class poly{
private:
    static constexpr auto MOD=998244353;
    static constexpr auto inv2=499122177;
    template<const int type>
    static auto fwtor(vector<lint>&a){
        const auto n=(int)(a.size());
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            for(auto i=0;i<n;i+=h){
                cir(k,0,midh){
                    (a[i+midh+k]+=type*a[i+k])%=MOD;
                }
            }
        }
    }
    template<const int type>
    static auto fwtand(vector<lint>&a){
        const auto n=(int)(a.size());
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            for(auto i=0;i<n;i+=h){
                cir(k,0,midh){
                    (a[i+k]+=type*a[i+midh+k])%=MOD;
                }
            }
        }
    }
    template<const int type>
    static auto fwtxor(vector<lint>&a){
        const auto n=(int)(a.size());
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            for(auto i=0;i<n;i+=h){
                cir(k,0,midh){
                    const auto las=a[i+k];
                    a[i+k]+=a[i+midh+k];
                    a[i+midh+k]=las-a[i+midh+k];
                    (a[i+k]*=type)%=MOD;
                    (a[i+midh+k]*=type)%=MOD;
                }
            }
        }
    }
    static auto chk(vector<lint>&a,vector<lint>&b){
        cir(i,0,(int)(a.size())) (a[i]*=b[i])%=MOD;
    }
    static auto chg(vector<lint>&a){
        for(auto&i:a) (i+=MOD)%=MOD;
        return a;
    }
public:
    static auto andop(vector<lint> a,vector<lint> b){
        fwtand<1>(a);fwtand<1>(b);
        chk(a,b);fwtand<-1>(a);
        return chg(a);
    }
    static auto orop(vector<lint> a,vector<lint> b){
        fwtor<1>(a);fwtor<1>(b);
        chk(a,b);fwtor<-1>(a);
        return chg(a);
    }
    static auto xorop(vector<lint> a,vector<lint> b){
        fwtxor<1>(a);fwtxor<1>(b);
        chk(a,b);fwtxor<inv2>(a);
        return chg(a);
    }
};
template<typename _Ty>
ostream&operator<<(ostream&os,vector<_Ty> x){
    for(auto&i:x) os<<i<<' ';
    return os;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<lint> a(1<<n),b(1<<n);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    cout<<poly::orop(a,b)<<'\n';
    cout<<poly::andop(a,b)<<'\n';
    cout<<poly::xorop(a,b)<<'\n';
    return 0;
}
