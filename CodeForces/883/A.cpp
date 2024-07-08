#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,ans=0;cin>>n;
        cir(i,0,n){
            int a,b;cin>>a>>b;ans+=(b<a);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
