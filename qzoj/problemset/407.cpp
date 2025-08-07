#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int k,n;cin>>k>>n;
    vector<int> w(n),ns(n);
    cir(i,0,n){
        cin>>w[i];
        int x;
        while(cin>>x&&x) ns[i]|=(1<<(x-1));
    }
    vector<vector<long double>> f(k,vector<long double>(1<<n));
    vector<vector<int>> vis(k,vector<int>(1<<n));
    auto dfs=[&](auto __self,int p,int s){
        if(p>k-1) return 0.0l;
        if(vis[p][s]) return f[p][s];
        vis[p][s]=true;
        auto&res=f[p][s];
        cir(i,0,n){
            auto mx=__self(__self,p+1,s);
            if((ns[i]&s)==ns[i]) mx=max(mx,__self(__self,p+1,s|(1<<i))+w[i]);
            res+=mx/n;
        }
        return res;
    };
    cout<<fixed<<setprecision(6)<<dfs(dfs,0,0)<<'\n';
    return 0;
}
