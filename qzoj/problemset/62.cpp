#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<vector<int>> vx(n+1);
    auto m=0;
    int u,v;
    vector<vector<int>> cnt(n+1,vector<int>(n+1));
    while(cin>>u>>v){
        ++m;
        vx[u].emplace_back(v);
        vx[v].emplace_back(u);
        ++cnt[min(u,v)][max(u,v)];
    }
    auto ok=true;
    for(auto&x:vx) ok&=(!(x.size()&1));
    if(!ok) exit((cout<<0<<'\n',0));
    vector<int> ans;
    auto dfs=[&](auto __self,int u)->void {
        while(!vx[u].empty()){
            const auto v=vx[u].back();vx[u].pop_back();
            if(!cnt[min(u,v)][max(u,v)]) continue;
            --cnt[min(u,v)][max(u,v)];
            __self(__self,v);
        }
        ans.emplace_back(u);
    };
    dfs(dfs,1);
    if((int)(ans.size())!=m+1){
        cout<<0<<'\n';
    }else{
        cout<<1<<'\n';
        for(auto&i:ans) cout<<i<<' ';
        cout<<'\n';
    }
    return 0;
}
