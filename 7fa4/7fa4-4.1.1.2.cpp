#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename T>
vector<T> Phi(T n){
    vector<T> ret(n+1);
    iota(ret.begin(),ret.end(),0);
    cir(i,2,n+1){
        if(ret[i]!=i) continue;
        for(auto j=i*2;j<=n;j+=i) (ret[j]/=i)*=(i-1);
    }
    return ret;
}
const int MAXN=1e6+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    vector<int> phi=Phi(MAXN);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        lint ans=0;
        cir(i,1,n) ans+=phi[i]*2;
        cout<<ans+phi[n]-n+1<<'\n';
    }
    return 0;

}