#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<int> a(n*2);
        for(auto&i:a) cin>>i;
        sort(a.begin(),a.end(),greater<int>());
        int ans=0;
        cir(i,0,n) ans+=a[i*2+1];
        cout<<ans<<'\n';
    }
    return 0;
}
