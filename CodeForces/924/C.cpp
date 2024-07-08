#include<bits/stdc++.h>
#define cir(i,a,b) for(int64_t i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int64_t T;cin>>T;
    while(T--){
        int64_t n,w;cin>>n>>w;
        set<int64_t> ans;
        //k+(k-w)=n => 2k-w=n => k=(n+w)/2;
        if(!((n+w)&1)) ans.insert((n+w)/2);
        //k≤√n
        for(int64_t k=2;1ll*k*k<n+1;++k){
            if(k>w-1&&(n-1)%(k*2-2)+1==w) ans.insert(k);
            if(k>w&&(n-1)%(k*2-2)+1==k+(k-w)) ans.insert(k);
        }
        for(int64_t x=1;1ll*x*x<n+1;++x){
            if((!((n-w)%x))) [&](){
                const auto kx=(n-w)/x;
                if(kx&1) return;
                const auto k=kx/2+1;
                if(k>w-1) ans.insert(k);
            }();
            const auto wi=n+w+x*2;
            if(!(wi%(x*2+2))){
                const auto k=wi/(x*2+2);
                if(k>w) ans.insert(k);
            }
        }
        if(w==2){
            for(int64_t x=2;x*x<n+1;++x){
                if(!(n%x)){
                    if(!(x&1)) ans.insert(x/2+1);
                    if(!((n/x)&1)) ans.insert((n/x/2)+1);
                }
            }
        }
        cout<<ans.size()<<'\n'<<flush;
    }
    return 0;
}
