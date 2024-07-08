#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<lint> a(n),f(n+2),pre(n+2);
    for(auto&i:a) cin>>i;
    [&](){
        f[2]=a[0];
        cir(i,3,n+2){
            if(f[i-3]+max(a[i-3],a[i-2])<f[i-2]+a[i-2]){
                f[i]=f[pre[i]=i-3]+max(a[i-3],a[i-2]);
            }else{
                f[i]=f[pre[i]=i-2]+a[i-2];
            }
        }
    }();
    vector<int> ans;
    auto ins=[&](int p){
        if(p==n||(!a[p-1])||(!a[p])) return;
        ans.push_back(p);
        const auto mn=min(a[p-1],a[p]);
        a[p-1]-=mn;a[p]-=mn;
    };
    for(auto i=(f[n]<f[n+1]?n:n+1);i>1;i=pre[i]){
        if(pre[i]==i-3){
            ins(i-2);ins(i-1);
            if(i>3) ins(i-3);
        }else{
            ins(i-1);
            if(i>2) ins(i-2);
        }
    }
    cout<<ans.size()<<'\n';
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
