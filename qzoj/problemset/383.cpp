#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=1234567;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<int>> v(1<<n);
    cir(s,0,(1<<n)){
        auto dfs=[&](auto __self,int p,int cur){
            if(p==n){
                v[s].emplace_back(cur);
                return;
            }
            if((s>>p)&1) return __self(__self,p+1,cur);
            __self(__self,p+1,cur|(1<<p));
            if(p+1<n&&(!((s>>(p+1))&1))) __self(__self,p+2,cur);
        };
        dfs(dfs,0,0);
    }
    vector<lint> f(1<<n),nf(1<<n);
    f[0]=1;
    cir(i,0,m){
        fill(nf.begin(),nf.end(),0);
        cir(s,0,(1<<n)) for(auto ns:v[s]) nf[ns]+=f[s];
        cir(i,0,(1<<n)) f[i]=nf[i]%MOD;
    }
    cout<<((n*m)&1?-1:f[0])<<'\n';
    return 0;
}
