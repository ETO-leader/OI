#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto mxv=(int)(1e7+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    vector<int> mnp(mxv);
    iota(mnp.begin(),mnp.end(),0);
    cir(i,2,mxv) if(mnp[i]==i){
        for(auto j=(int64_t)(i)*i;j<mxv;j+=i) mnp[j]=min(mnp[j],i);
    }
    vector<lint> mu(mxv);
    mu[1]=1;
    cir(i,2,mxv){
        if(!((i/mnp[i])%mnp[i])) mu[i]=0;
        else mu[i]=-mu[i/mnp[i]];
    }
    vector<lint> pf(mxv);
    mnp[0]=mnp[1]=-1;
    cir(i,1,mxv) if(mnp[i]==i){
        for(auto v=i,c=1;v<mxv;v+=i,++c) pf[v]+=mu[c];
    }
    cir(i,1,mxv) pf[i]+=pf[i-1];
    auto f=[&](int n,int m){
        auto res=0ll;
        for(auto i=1,r=0;i<min(n,m)+1;i=r+1){
            r=min(n/(n/i),m/(m/i));
            res+=(pf[r]-pf[i-1])*(n/i)*(m/i);
        }
        return res;
    };
    while(T--) [&]{
        int a,b;cin>>a>>b;
        cout<<f(a,b)<<'\n';
    }();
    return 0;
}
