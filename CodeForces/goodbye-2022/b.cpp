#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,k;cin>>n>>k;
        vector<int> ans(n);
        auto p=n-k,lw=0,rw=n+1;
        for(auto i=n-1;~i;--i){
            if(i==p) ans[i]=++lw,p-=k;
            else ans[i]=--rw;
        }
        for(auto&i:ans) cout<<i<<' ';
        cout<<'\n';
    }();
    return 0;
}
