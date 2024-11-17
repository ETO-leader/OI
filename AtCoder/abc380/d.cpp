#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    auto divide=[&](auto __self,lint l,lint r,lint p)->bool {
        if(l==r) return false; 
        const auto mid=(l+r)/2;
        if(p<mid+1) return __self(__self,l,mid,p);
        return __self(__self,l,mid,p-mid-1)^true; 
    };
    int q;cin>>q;
    cir(i,0,q){
        lint x;cin>>x;--x;
        const auto rv=divide(divide,0,(1ll<<62)-1,x/s.size());
        auto ansc=s[x%s.size()];
        if(rv){
            if('a'<ansc+1) ansc-='a'-'A';
            else ansc+='a'-'A';
        }
        cout<<ansc<<' ';
    }
    cout<<'\n';
    return 0;
}
