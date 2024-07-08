#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
lint calc(lint ix,lint n){
    return max(ix-1-max(ix-n-1,0LL)*2,0LL);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,k,ans=0;cin>>n>>k;
    cir(i,2,2*n+1){
        if(i<(k+2)) continue;
        ans+=calc(i,n)*calc(i-k,n);
    }
    cout<<ans<<'\n';
    return 0;
}
