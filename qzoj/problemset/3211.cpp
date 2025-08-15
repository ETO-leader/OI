#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto mxv=(int)(1e7+7);
static constexpr auto MOD=(int)(1e8+9);
constexpr auto s(lint x){
    return (x+1)*x/2;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    vector<int> mnp(mxv);
    iota(mnp.begin(),mnp.end(),0);
    cir(i,2,mxv) if(mnp[i]==i){
        for(auto j=(int64_t)(i)*i;j<mxv;j+=i) mnp[j]=min(mnp[j],i);
    }
    vector<lint> mu(mxv),pf(mxv);
    mu[1]=1;pf[1]=1;
    cir(i,2,mxv){
        pf[i]=pf[i/mnp[i]];
        if(!((i/mnp[i])%mnp[i])) mu[i]=0;
        else mu[i]=-mu[i/mnp[i]],pf[i]+=pf[i/mnp[i]]*(-mnp[i]);
    }
    mnp[0]=mnp[1]=-1;
    cir(i,1,mxv) (pf[i]*=i)+=pf[i-1];
    auto f=[&](int n,int m){
        auto res=(__int128_t)(0);
        for(auto i=1,r=0;i<min(n,m)+1;i=r+1){
            r=min(n/(n/i),m/(m/i));
            res+=(__int128_t)(pf[r]-pf[i-1])*s(n/i)*s(m/i);
        }
        return (lint)((res%MOD+MOD)%MOD);
    };
    while(T--) [&]{
        int a,b;cin>>a>>b;
        cout<<f(a,b)<<'\n';
    }();
    return 0;
}
