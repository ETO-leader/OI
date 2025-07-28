#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        lint a,b,k;cin>>a>>b>>k;
        cout<<(max(a/gcd(a,b),b/gcd(a,b))>k)+1<<'\n';
    }();
    return 0;
}
