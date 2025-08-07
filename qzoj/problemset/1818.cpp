#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
constexpr auto isprime(int x){
    for(auto w=2ll;w*w<x+1;++w) if(!(x%w)) return false;
    return true;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint n;cin>>n;
    vector<int> vals;
    auto pw=1ll;
    auto x=2;
    auto ans=make_pair(-1ll,-1ll);
    while(pw*x<n+1){
        if(isprime(x)) pw*=x,vals.emplace_back(x);
        ++x;
    }
    auto dfs=[&](auto __self,int p,int l,lint w,lint c)->void {
        if(p==(int)(vals.size())) return ans=max(ans,{c,-w}),void();
        cir(i,0,l+1){
            if(w>n) break;
            __self(__self,p+1,i,w,c*(i+1));
            w*=vals[p];
        }
    };
    dfs(dfs,0,30,1,1);
    cout<<-ans.second<<'\n';
    return 0;
}
