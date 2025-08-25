#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector<pair<int,int>> op;
        if(-*ranges::min_element(a)<*ranges::max_element(a)+1){
            const auto mnp=ranges::min_element(a)-a.begin();
            const auto mxp=ranges::max_element(a)-a.begin();
            if(ranges::count_if(a,[](auto x){return x<0;})<13){
                cir(i,0,n) if(a[i]<0) op.emplace_back(i,mxp);
                cir(i,1,n) op.emplace_back(i,i-1);
            }else{
                cir(i,0,5) op.emplace_back(mnp,mnp);
                cir(i,0,n) if(a[i]>0) op.emplace_back(i,mnp);
                for(auto i=n-1;i;--i) op.emplace_back(i-1,i);
            }
        }else{
            const auto mnp=ranges::min_element(a)-a.begin();
            const auto mxp=ranges::max_element(a)-a.begin();
            if(ranges::count_if(a,[](auto x){return x>0;})<13){
                cir(i,0,n) if(a[i]>0) op.emplace_back(i,mnp);
                for(auto i=n-1;i;--i) op.emplace_back(i-1,i);
            }else{
                cir(i,0,5) op.emplace_back(mxp,mxp);
                cir(i,0,n) if(a[i]<0) op.emplace_back(i,mxp);
                cir(i,1,n) op.emplace_back(i,i-1);
            }
        }
        cout<<op.size()<<'\n';
        for(auto&[a,b]:op) cout<<a+1<<' '<<b+1<<'\n';
    }();
    return 0;
}
