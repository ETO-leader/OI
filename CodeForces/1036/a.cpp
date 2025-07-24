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
        if(ranges::is_sorted(a)) return cout<<"NO"<<'\n',void();
        cout<<"YES"<<'\n';
        cir(i,0,n) cir(j,i+1,n) if(a[i]>a[j]){
            cout<<2<<'\n';
            cout<<a[i]<<' '<<a[j]<<'\n';
            return;
        }
    }();
    return 0;
}
