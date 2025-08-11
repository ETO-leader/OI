#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> w(n);
    for(auto&i:w) cin>>i;
    const auto mx=*max_element(w.begin(),w.end());
    vector<int> cnt(mx+1),ans(mx+1);
    for(auto&i:w) ++cnt[i];
    cir(i,1,mx+1){
        for(auto j=i;j<mx+1;j+=i) ans[j]+=cnt[i];
    }
    for(auto&i:w) cout<<ans[i]-1<<'\n';
    return 0;
}
