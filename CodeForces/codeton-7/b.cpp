#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        string s;cin>>s;
        auto p=0;
        cir(i,0,n){
            if(s[i]=='A') break;
            p=i+1;
        }
        while((!s.empty())&&s.back()=='A') s.pop_back();
        cout<<max((int)(s.size())-1-p,0)<<'\n';
    }();
    return 0;
}
