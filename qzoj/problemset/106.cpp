#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    auto ans=0ll,sum=0ll;
    for(auto&x:a){
        sum=max(sum+x,0ll);
        ans=max(ans,sum);
    }
    cout<<ans<<'\n';
    return 0;
}
