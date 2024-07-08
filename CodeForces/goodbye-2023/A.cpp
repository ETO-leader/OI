#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,k;cin>>n>>k;
        lint prd=1;
        cir(i,0,n){
            lint x;cin>>x;prd*=x;
        }
        if(2023%prd)
            return cout<<"NO\n",void();
        cout<<"YES\n";
        cir(i,0,k-1) cout<<1<<' ';
        cout<<2023/prd<<'\n';
    }();
    return 0;
}