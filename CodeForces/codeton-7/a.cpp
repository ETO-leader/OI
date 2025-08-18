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
        cout<<(a[0]==1?"YES":"NO")<<'\n';
    }();
    return 0;
}
