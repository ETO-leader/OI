#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        vector<lint> a(n),b(n);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i;
        const auto suma=accumulate(
            a.begin(),a.end(),(lint)(0));
        const auto sumb=accumulate(
            b.begin(),b.end(),(lint)(0));
        const auto mna=*min_element(
            a.begin(),a.end())*n;
        const auto mnb=*min_element(
            b.begin(),b.end())*n;
        cout<<min(suma+mnb,sumb+mna)<<'\n';
    }
    return 0;
}
