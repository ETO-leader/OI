#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        auto ans=numeric_limits<lint>::max(),pre=0ll;
        auto pmn=numeric_limits<int>::max();
        cir(i,0,n-1){
            ans=min(ans,pre+min(pmn,a[i]+a[i+1]));
            pre+=(pmn=min(pmn,a[i]));
        }
        ans=min(ans,pre+min(pmn,a[n-1]));
        cout<<ans<<'\n';
    }();
    return 0;
}
