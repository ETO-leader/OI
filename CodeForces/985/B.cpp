#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        string a,b;cin>>a>>b;
        const auto c0a=count(a.begin(),a.end(),'0');
        const auto c1a=count(a.begin(),a.end(),'1');
        const auto c0b=count(b.begin(),b.end()-1,'0');
        const auto c1b=count(b.begin(),b.end()-1,'1');
        println("{}",(c0a>c1b&&c1a>c0b)?"YES":"NO");
    }();
    return 0;
}
