#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
constexpr auto getminp(int x){
    for(auto i=2;i*i<x+1;++i)
        if(!(x%i)) return i;
    return x;
}
auto init_premu(int n){
    vector<int> mu(n);mu[1]=1;
    cir(i,2,n){
        const auto minp=getminp(i);
        if(!(i/minp%minp)) continue;
        mu[i]=-mu[i/minp];
    }
    cir(i,2,n) mu[i]+=mu[i-1];
    return mu;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    const auto pmu=init_premu(50007);
    auto calc=[pmu](int n,int m){
        auto ans=0;
        for(auto i=1,p=0;i<min(n,m)+1;i=p+1){
            p=min(n/(n/i),m/(m/i));
            ans+=(pmu[p]-pmu[i-1])*(n/i)*(m/i);
        }
        return ans;
    };
    while(T--){
        int a,b,c,d,k;cin>>a>>b>>c>>d>>k;
        (a-=1)/=k;b/=k;(c-=1)/=k;d/=k;
        cout<<calc(b,d)-calc(a,d)-calc(b,c)+calc(a,c)<<'\n';
    }
    return 0;
}
