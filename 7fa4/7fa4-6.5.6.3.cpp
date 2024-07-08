#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename _Ty,class comp=less<_Ty>>
using heap=__gnu_pbds::priority_queue<
    _Ty,comp,__gnu_pbds::pairing_heap_tag>;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    vector<lint> fx(n+m+1),w(n+m+1),deg(n+1);
    cir(i,2,n+m+1){
        cin>>fx[i]>>w[i];++deg[fx[i]];
    }
    auto ans=accumulate(
        w.begin(),w.end(),(lint)(0));
    vector<heap<lint>> pqs(n+m+1);
    auto get=[&](int u){
        if(pqs[u].empty()) return (lint)(0);
        auto res=pqs[u].top();pqs[u].pop();
        return res;
    };
    for(int u=n+m;u>1;--u){
        if(u<n+1) while(--deg[u]) get(u);
        const auto r=get(u),l=get(u);
        pqs[u].push(w[u]+l);
        pqs[u].push(w[u]+r);
        pqs[fx[u]].join(pqs[u]);
    }
    while(deg[1]--) get(1);
    while(!pqs[1].empty()) ans-=get(1);
    cout<<ans<<'\n';
    return 0;
}
