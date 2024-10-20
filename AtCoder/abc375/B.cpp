#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    complex<long double> cur(0,0);
    auto ans=0.0l;
    cir(i,0,n){
        int x,y;cin>>x>>y;
        const auto px=complex<long double>(x,y);
        ans+=abs(cur-px);
        cur=px;
    }
    cout<<fixed<<setprecision(15)<<ans+abs(cur)<<'\n';
    return 0;
}
