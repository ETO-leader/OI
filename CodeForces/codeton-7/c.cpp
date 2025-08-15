#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,x;cin>>n>>x;
        vector<int> a(n),b(n);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i;
        vector<int> pos(n);
        ranges::iota(pos,0);
        ranges::sort(pos,[&](int u,int v){return a[u]>a[v];});
        ranges::sort(b);
        vector<int> ab(n);
        cir(i,0,n){
            if(i<x) ab[pos[i]]=b[x-i-1];
            else ab[pos[i]]=b[n-1+x-i];
        }
        auto cnt=0;
        cir(i,0,n) cnt+=(a[i]>ab[i]);
        if(cnt==x){
            cout<<"YES"<<'\n';
            for(auto&x:ab) cout<<x<<' ';
            cout<<'\n';
        }else{
            cout<<"NO"<<'\n';
        }
    }();
    return 0;
}
