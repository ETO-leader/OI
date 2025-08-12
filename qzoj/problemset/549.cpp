#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto lim=(int)(1e6);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    uint64_t a,b,c;cin>>a>>b>>c;
    auto w=(uint64_t)(1);
    auto cnt=0,ans=-1;
    unordered_set<uint32_t> apr{w};
    while(cnt<lim){
        w=(w*a+w%b)%c;
        ++cnt;
        if(apr.count(w)){
            ans=cnt;
            break;
        }
        apr.emplace(w);
    }
    cout<<ans<<'\n';
    return 0;
}
