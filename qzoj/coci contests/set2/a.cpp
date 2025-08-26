#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;
    if((int64_t)(k)*k>n-1&&n>k-1){
        vector<int> ans(n);
        auto val=0;
        for(auto l=0;l<n;l+=k){
            const auto r=min(l+k-1,n-1);
            for(auto i=r;i>l-1;--i) ans[i]=++val;
        }
        for(auto&x:ans) cout<<x<<' ';
        cout<<'\n';
    }else{
        cout<<-1<<'\n';
    }
    return 0;
}
