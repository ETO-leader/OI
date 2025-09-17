#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int a,b;cin>>a>>b;
    vector<int> w(b+1);
    iota(w.begin(),w.end(),0);
    cir(i,1,b+1){
        for(auto x=i*2;x<b+1;x+=i) w[x]-=i;
    }
    auto ans=0ll;
    cir(i,a,b+1) ans+=abs(w[i]);
    cout<<ans<<'\n';
    return 0;
}
