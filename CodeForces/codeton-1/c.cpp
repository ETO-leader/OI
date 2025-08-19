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
        if(ranges::count(a,1)){
            ranges::sort(a);
            cir(i,1,n) if(a[i]-a[i-1]==1) return cout<<"NO"<<'\n',void();
            cout<<"YES"<<'\n';
        }else{
            cout<<"YES"<<'\n';
        }
    }();
    return 0;
}
