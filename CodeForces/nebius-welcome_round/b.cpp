#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,k,d,w;cin>>n>>k>>d>>w;
        vector<int> t(n);
        for(auto&i:t) cin>>i;
        auto cur=0,disable=-1;
        auto ans=0;
        for(auto&x:t){
            if((!cur)||disable<x){
                cur=k;disable=x+w+d;
                ++ans;
            }
            --cur;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
