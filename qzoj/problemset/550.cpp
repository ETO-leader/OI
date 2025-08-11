#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    unordered_map<int,int> cnt;
    auto l=0,ans=0;
    cir(r,0,n){
        while(cnt[a[r]]) --cnt[a[l]],++l;
        ++cnt[a[r]];
        ans=max(ans,r-l+1);
    }
    cout<<ans<<'\n';
    return 0;
}
