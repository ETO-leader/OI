#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        if(n&1) cout<<-1<<'\n';
        else cout<<n/2<<' '<<1<<'\n';
    }();
    return 0;
}
