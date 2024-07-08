#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        cir(i,1,n) a[i]+=a[i-1];
        const auto mx=max(*max_element(
            a.begin(),a.end()),(lint)(0));
        const auto mn=min(*min_element(
            a.begin(),a.end()),(lint)(0));
        cout<<mx-mn<<'\n';
    }
    return 0;
}
