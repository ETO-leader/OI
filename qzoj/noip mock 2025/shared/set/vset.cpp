#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream inf("set.in");
ofstream ouf("set.out");
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;cin>>n;
    const auto k=(1<<n)-1;
    auto ans=0;
    cir(s,0,(1ll<<k)){
        vector<int> qwq;
        cir(i,0,k) if((s>>i)&1) qwq.emplace_back(i+1);
        auto ok=true;
        cir(i,0,(int)(qwq.size())) cir(j,0,(int)(qwq.size())) if(i!=j) ok&=((qwq[i]&qwq[j])!=qwq[i]);
        if(ok) ans=max(ans,__builtin_popcount(s));
    }
    cout<<ans<<'\n';
    return 0;
}

