#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        lint n,k;cin>>n>>k;
        auto dfs=[&](auto __self,lint len)->pair<lint,lint> {
            if(len<k) return pair(0ll,0ll);
            if(!(len%2)){
                const auto[w,c]=__self(__self,len/2);
                return pair(w*2+c*len/2,c*2);
            }else{
                const auto[w,c]=__self(__self,len/2);
                return pair(w*2+(len/2+1)+c*(len/2+1),c*2+1);
            }
        };
        println("{}",dfs(dfs,n).first);
    }();
    return 0;
}
