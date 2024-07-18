#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        string b;cin>>b;
        ranges::reverse(a);
        ranges::reverse(b);
        priority_queue<int,vector<int>,greater<int>> q;
        auto ans=0ll;
        cir(i,0,n){
            q.push(a[i]);
            if(b[i]=='1') ans+=q.top(),q.pop();
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
