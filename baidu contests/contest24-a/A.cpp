#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;lint m;cin>>n>>m;
    vector<pair<lint,lint>> cst(n);
    for(auto&[a,b]:cst) cin>>a>>b;
    sort(cst.begin(),cst.end(),[&](auto&a,auto&b){
        return a.first+a.second<b.first+b.second;
    });
    vector<lint> pre(n);
    [&](){
        auto pr=0ll;
        cir(i,0,n){
            pre[i]=(pr+=cst[i].first+cst[i].second);
        }
    }();
    auto fnd=[&](lint w){
        return upper_bound(pre.begin(),pre.end(),w)-pre.begin();
    };
    auto ans=0;
    cir(i,0,n){
        const auto chsw=cst[i].first/2+cst[i].second;
        if(chsw>m) continue;
        const auto pw=(i?pre[i-1]:0ll)+chsw;
        if(pw>m-1){
            ans=max<int>(ans,fnd(m-chsw)+1);
        }else{
            ans=max<int>(ans,fnd(m+(cst[i].first-cst[i].first/2)));
        }
    }
    cout<<ans<<'\n';
    return 0;
}
