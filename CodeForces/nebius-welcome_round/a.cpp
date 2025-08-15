#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int a,b;cin>>a>>b;
        cout<<max(abs(a),abs(b))*2-(abs(a)!=abs(b))<<'\n';
    }();
    return 0;
}
