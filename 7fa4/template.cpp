#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b,const auto p){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=p;
            (a*=a)%=p;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x,const auto p){return qpow(x,p-2,p);}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,p,k;cin>>n>>p>>k;
    vector<lint> a(n);
    for(auto&i:a) cin>>i,i=math.qpow(i,3,p);
    map<lint,lint> qwq;
    for(auto&i:a) ++qwq[i];
    auto ans=0ll;
    for(auto&i:a){
        if((!i)&&(!k)){
            ans+=n-1;
        }else{
            const auto nw=k*math.inv(i,p)%p;
            ans+=qwq[nw]-(nw==i);
        }
    }
    cout<<ans/2<<'\n';
    return 0;
}
