#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        string s;cin>>s;
        string ans;
        for(auto&x:s) if(x=='T') ans+=x;
        for(auto&x:s) if(x!='T') ans+=x;
        cout<<ans<<'\n';
    }();
    return 0;
}
