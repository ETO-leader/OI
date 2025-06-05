#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T,p;cin>>T>>p;
    while(T--) [p]{
        lint n;cin>>n;
        map<tuple<int,int,int>,lint> f;
        auto dfs=[&](auto __self,lint u,lint gc,lint lc){
            if(n%lc) return 0ll;
            if(u>n) return (lint)(gc==1&&lc==n);
            if(f.contains({u,gc,lc})) return f[{u,gc,lc}];
            return (__self(__self,u+1,gcd(gc,u),lcm(lc,u))+__self(__self,u+1,gc,lc))%p;
        };
        cout<<dfs(dfs,1,0,1)<<'\n';
    }();
    return 0;
}
