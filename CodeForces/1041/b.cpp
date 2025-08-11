#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,p;cin>>n>>p;--p;
        string s;cin>>s;
        auto lp=-1,rp=n;
        cir(i,0,p) if(s[i]=='#') lp=i;
        for(auto i=n-1;i>p;--i) if(s[i]=='#') rp=i;
        const auto ansl=min(p,n-rp);
        const auto ansr=min(lp+1,n-p-1);
        cout<<max(ansl,ansr)+1<<'\n';
    }();
    return 0;
}
