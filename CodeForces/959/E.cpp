#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int k;cin>>k;
        vector<int> sz(k);
        cir(i,0,k){
            int n;cin>>n;sz[i]=n;
            vector<int> f(n);
            cir(i,1,n) cin>>f[i];
        }
        ranges::sort(sz,greater<int>());
        auto ans=0;
        for(auto&x:sz){
            for(auto i=21;~i;--i){
                if((!(ans&(1<<i)))&&x>(1<<i)-1) ans|=(1<<i),x-=(1<<i);
            }
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
