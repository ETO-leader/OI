#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k,ans=0;cin>>n>>m>>k;
    auto in_range=[&k](int nw,int c){
        return nw>=(c-k)&&nw<=(c+k);};
    deque<int> peo(n),apa(m);
    for(auto&i:peo) cin>>i;
    sort(peo.begin(),peo.end());
    for(auto&i:apa) cin>>i;
    sort(apa.begin(),apa.end());
    for(auto&i:peo){
        while(!apa.empty()&&apa.front()<i-k) apa.pop_front();
        if(apa.empty()) break;
        if(in_range(i,apa.front())) ++ans,apa.pop_front();
    }
    cout<<ans<<'\n';
    return 0;
}