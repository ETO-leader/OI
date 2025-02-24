#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    int m;cin>>m;
    cir(i,0,m){
        int c;cin>>c;
        vector<int> target(c);
        for(auto&x:target) cin>>x;
        auto ans=0;
        cir(s,0,(1<<n)){
            auto ok=true;
            for(auto&i:target){
                auto okx=false;
                cir(c,0,n) if(s&(1<<c)) okx|=(!(a[c]%i));
                ok&=okx;
            }
            ans+=ok;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
