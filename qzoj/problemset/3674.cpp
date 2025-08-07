#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> cur;
    auto dfs=[&](auto __self,int p){
        if(p==n){
            for(auto&i:cur) cout<<i<<' ';
            cout<<'\n';
            return;
        }
        cir(i,1,4) if(p+i<n+1) cur.emplace_back(i),__self(__self,p+i),cur.pop_back();
    };
    dfs(dfs,0);
    return 0;
}
