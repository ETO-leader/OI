#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,k;cin>>n>>k;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        const auto s=set(a.begin(),a.end());
        cir(i,0,n) if(s.contains(a[i]-k)) return cout<<"YES"<<'\n',void();
        cout<<"NO"<<'\n';
    }();
    return 0;
}
