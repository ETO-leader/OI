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
        vector<int> ans(n);
        auto mn=0,mx=0;
        cir(i,0,n-1){
            if(s[i]=='<') ans[i+1]=mn-1;
            else ans[i+1]=mx+1;
            mn=min(mn,ans[i+1]);
            mx=max(mx,ans[i+1]);
        }
        for(auto&i:ans) cout<<i-mn+1<<' ';
        cout<<'\n';
    }();
    return 0;
}
