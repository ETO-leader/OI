#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;lint k;cin>>n>>k;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        const auto mx=*ranges::max_element(a);
        const auto sum=accumulate(a.begin(),a.end(),0ll);
        for(auto siz=n;~siz;--siz){
            const auto nd=max((sum+siz-1)/siz,mx);
            if(siz*nd-sum<k+1) return println("{}",siz);
        }
        println("");
    }();
    return 0;
}
